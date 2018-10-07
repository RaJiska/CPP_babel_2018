/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Server
*/

#include <string>
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include "Server.hpp"

Server::Server(const std::string &address, uint16_t port, MainWindow &window) :
	window(window), socket(this->io_service)
{
	boost::asio::ip::tcp::endpoint endp(
		boost::asio::ip::address::from_string(address), port);
	this->socket.connect(endp);
	this->msgMap[NetworkMessage::Header::TYPE_LOGIN] =
	std::bind(&Server::handleLoginMsg, this, std::placeholders::_1);
	this->msgMap[NetworkMessage::Header::TYPE_LOGOUT] =
	std::bind(&Server::handleLogoutMsg, this, std::placeholders::_1);
	this->msgMap[NetworkMessage::Header::TYPE_CALL] =
	std::bind(&Server::handleCallMsg, this, std::placeholders::_1);
	this->msgMap[NetworkMessage::Header::TYPE_HANGUP] =
	std::bind(&Server::handleHangupMsg, this, std::placeholders::_1);
	this->msgMap[NetworkMessage::Header::TYPE_QUERY] =
	std::bind(&Server::handleQueryMsg, this, std::placeholders::_1);
	this->start();
}

Server::~Server()
{
	this->socket.close();
}

void Server::sendLoginMsg(const std::string &name) noexcept
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
}

void Server::handleLoginMsg(NetworkMessage msg) noexcept
{
	struct NetworkMessage::Header &header = msg.getHeader();
	struct NetworkMessage::MsgLogin *data =
		(struct NetworkMessage::MsgLogin *) msg.getData();
	if (header.from == header.to)
		this->clientId = data->id;
}

void Server::sendLogoutMsg() noexcept
{
	NetworkMessage msg;
	struct NetworkMessage::Header &header = msg.getHeader();
	header.from = 0;
	header.to = 0;
	header.type = NetworkMessage::Header::MessageType::TYPE_LOGOUT;
	header.size = sizeof(struct NetworkMessage::MsgLogout);
	this->sendMessage(msg);
}

void Server::handleLogoutMsg(NetworkMessage msg) noexcept
{
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
	msg.setData((const unsigned char *) &mcall, header.size);
	this->sendMessage(msg);
}

void Server::handleCallMsg(NetworkMessage msg) noexcept
{
	this->window.handleCall(*(NetworkMessage::MsgCall *) msg.getData());
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

void Server::handleHangupMsg(NetworkMessage msg) noexcept
{
	this->window.handleHangup();
}

void Server::sendQueryMsg(const std::string &name) noexcept
{
	NetworkMessage msg;
	struct NetworkMessage::Header &header = msg.getHeader();
	header.from = 0;
	header.to = 0;
	header.type = NetworkMessage::Header::MessageType::TYPE_QUERY;
	header.size = sizeof(struct NetworkMessage::MsgQuery);
	struct NetworkMessage::MsgQuery *data =
		(struct NetworkMessage::MsgQuery *) msg.getData();
	std::strncpy(data->name, name.c_str(), 31)[31] = 0;
	this->sendMessage(msg);
}

void Server::handleQueryMsg(NetworkMessage msg) noexcept
{
	this->window.handleContact(*(NetworkMessage::MsgQuery *) msg.getData());
}

void Server::sendMessage(NetworkMessage &msg) noexcept
{
	boost::asio::async_write(this->socket, boost::asio::buffer(
		boost::asio::buffer(&msg.getHeader(), sizeof(msg.getHeader()))),
		boost::bind(&Server::handleWrite, this,
		boost::asio::placeholders::error));
	boost::asio::async_write(this->socket, boost::asio::buffer(
		boost::asio::buffer(msg.getData(), msg.getHeader().size)),
		boost::bind(&Server::handleWrite, this,
			boost::asio::placeholders::error));
}

void Server::handleWrite(
	const boost::system::error_code &err) noexcept
{
}

void Server::start() noexcept
{
	this->socket.async_read_some(
		boost::asio::buffer(memset(&this->readData[0], 0, 8192),
			sizeof(NetworkMessage::Header)),
		boost::bind(&Server::handleReadHeader, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void Server::handleReadHeader(
	const boost::system::error_code &err, size_t bytes_transferred)
{
	std::memcpy(&this->msg.getHeader(), &this->readData[0],
		sizeof(NetworkMessage::Header));
	this->socket.async_read_some(
		boost::asio::buffer(memset(&this->readData[0], 0, 8192),
			this->msg.getHeader().size),
		boost::bind(&Server::handleReadData, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void Server::handleReadData(
	const boost::system::error_code &err, size_t bytes_transferred)
{
	this->msg.setData(this->readData, this->msg.getHeader().size);
	try {
		this->msgMap[this->msg.getHeader().type](msg);
	}
	catch (std::exception &e) {
	}
	this->start();
}

void Server::run() noexcept
{
	this->io_service.run();
}