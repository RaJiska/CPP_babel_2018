/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Server
*/

#include <string>
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
	header.type == NetworkMessage::Header::MessageType::TYPE_LOGIN;
	msg.setData((const unsigned char *) name.c_str(), 32);
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

}
