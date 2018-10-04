/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Server
*/

#include <string>
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp>
#include "Server.hpp"

Server::Server(const std::string &address, uint16_t port)
{
	this->socket.connectToHost(QString::fromStdString(address), port);
	if (!this->socket.waitForConnected())
		throw std::logic_error("Connection timeout");
}

Server::~Server()
{
	this->socket.disconnect();
}

NetworkMessage Server::sendLoginMsg(const std::string &name) noexcept
{
	NetworkMessage msg;
	struct NetworkMessage::Header &header = msg.getHeader();
	header.from = 0;
	header.to = 0;
	header.type = NetworkMessage::Header::MessageType::TYPE_LOGIN;
	header.size = sizeof(struct NetworkMessage::MsgLogin);
	struct NetworkMessage::MsgLogin mlogin;
	std::strcpy(&mlogin.name[0], name.c_str());
	msg.setData((const unsigned char *) &mlogin, header.size);
	this->sendMessage(msg);
	return (this->readMessage());
}

NetworkMessage Server::sendLogoutMsg() noexcept
{
	NetworkMessage msg;
	struct NetworkMessage::Header &header = msg.getHeader();
	header.from = 0;
	header.to = 0;
	header.type = NetworkMessage::Header::MessageType::TYPE_LOGOUT;
	header.size = sizeof(struct NetworkMessage::MsgLogout);
	this->sendMessage(msg);
	return (this->readMessage());
}

void Server::sendCallMsg(unsigned long long int target) noexcept
{
	NetworkMessage msg;
	struct NetworkMessage::Header &header = msg.getHeader();
	header.from = 0;
	header.to = target;
	header.type = NetworkMessage::Header::MessageType::TYPE_CALL;
	header.size = sizeof(struct NetworkMessage::MsgCall);
	struct NetworkMessage::MsgCall mcall;
	/* set IP address */
	msg.setData((const unsigned char *) &mcall, header.size);
	this->sendMessage(msg);
}

void Server::sendHangupMsg(unsigned long long int target) noexcept
{
	NetworkMessage msg;
	struct NetworkMessage::Header &header = msg.getHeader();
	header.from = 0;
	header.to = target;
	header.type = NetworkMessage::Header::MessageType::TYPE_HANGUP;
	header.size = 0;
	this->sendMessage(msg);
}

void Server::sendMessage(NetworkMessage &msg) noexcept
{
	struct NetworkMessage::Header header = msg.getHeader();
	this->socket.write((const char *) &header,
		sizeof(struct NetworkMessage::Header));
	this->socket.write((const char *) msg.getData(), msg.getHeader().size);
	this->socket.waitForBytesWritten();
}

NetworkMessage Server::readMessage() noexcept
{
	QByteArray buf;
	this->readNBytes(buf, sizeof(struct NetworkMessage::Header));
	NetworkMessage msg;
	std::memcpy(&msg.getHeader(),
		buf.data(), sizeof(struct NetworkMessage::Header));
	buf.clear();
	this->readNBytes(buf, msg.getHeader().size);
	msg.setData((const unsigned char *) buf.data(), msg.getHeader().size);
	return (msg);
}

void Server::readNBytes(QByteArray &arr, qint64 nBytes) noexcept
{
	while (arr.size() < nBytes) {
		arr += this->socket.read(
			qMin(nBytes, this->socket.bytesAvailable()));
		boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
	}
}
