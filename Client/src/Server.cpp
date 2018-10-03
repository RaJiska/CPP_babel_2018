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

bool Server::sendLoginMsg(const std::string &name) noexcept
{
	NetworkMessage msg;
	struct NetworkMessage::Header &header = msg.getHeader();
	header.from = 0;
	header.to = 0;
	header.type = NetworkMessage::Header::MessageType::TYPE_LOGIN;
	header.size = sizeof(struct NetworkMessage::MsgLogin);
	struct NetworkMessage::MsgLogin mlogin;
	std::strcpy(&mlogin.name[0], name.c_str());
	msg.setData((const unsigned char *) &mlogin,
		sizeof(struct NetworkMessage::MsgLogin));
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

void Server::readMessage(NetworkMessage &msg) noexcept
{
	QByteArray buf;
	this->readNBytes(buf, sizeof(struct NetworkMessage::Header));
	std::memcpy(&msg.getHeader(),
		buf.data(), sizeof(struct NetworkMessage::Header));
	buf.clear();
	this->readNBytes(buf, msg.getHeader().size);
	msg.setData((const unsigned char *) buf.data(), msg.getHeader().size);
}

void Server::readNBytes(QByteArray &arr, qint64 nBytes) noexcept
{
	while (arr.size() < nBytes) {
		arr += this->socket.read(
			qMin(nBytes, this->socket.bytesAvailable()));
		boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
	}
}
