/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream> // DBG
#include "NetworkClient.hpp"

NetworkClient::NetworkClient(Server &server,
	unsigned long long int id, boost::asio::io_service &service) :
	server(server), id(id), socket(service)
{
	this->msgMap[NetworkMessage::Header::TYPE_ERROR] = std::bind(&NetworkClient::handleMsgError, this, std::placeholders::_1);
	this->msgMap[NetworkMessage::Header::TYPE_LOGIN] = std::bind(&NetworkClient::handleMsgLogin, this, std::placeholders::_1);
	this->msgMap[NetworkMessage::Header::TYPE_LOGOUT] = std::bind(&NetworkClient::handleMsgLogout, this, std::placeholders::_1);
}

NetworkClient::~NetworkClient()
{
}

void NetworkClient::start()
{
	try {
		while (true) {
			this->socket.read_some(boost::asio::buffer(memset(&this->readData[0], 0, 8192), sizeof(NetworkMessage::Header)));
			struct NetworkMessage::Header header;
			std::memcpy(&header, &this->readData[0], sizeof(NetworkMessage::Header));
			this->socket.read_some(boost::asio::buffer(memset(&this->readData[0], 0, 8192), header.size));
			NetworkMessage msg(header);
			msg.setData(this->readData, header.size);
			this->msgMap[header.type](msg);
		}
	}
	catch (std::exception &e) {
		this->disconnect(e.what());
	}
}

void NetworkClient::sendMessage(NetworkMessage &msg) noexcept
{
	boost::asio::async_write(this->socket, boost::asio::buffer(boost::asio::buffer(&msg.getHeader(), sizeof(msg.getHeader()))),
		boost::bind(&NetworkClient::handleWrite, this,
			boost::asio::placeholders::error));
	boost::asio::async_write(this->socket, boost::asio::buffer(boost::asio::buffer(msg.getData(), msg.getHeader().size)),
		boost::bind(&NetworkClient::handleWrite, this,
			boost::asio::placeholders::error));
}

void NetworkClient::handleWrite(
	const boost::system::error_code &err) noexcept
{
	if (err)
		this->disconnect(err.message());
}

void NetworkClient::disconnect(const std::string &reason) noexcept
{
	std::cout << "Client " << this->id <<
		" disconnected: " << reason << std::endl;
	this->socket.close();
	this->server.cleanClosedPeers();
}

void NetworkClient::handleMsgError(NetworkMessage &msg) const noexcept
{
}

void NetworkClient::handleMsgLogin(NetworkMessage &msg) noexcept
{
	struct NetworkMessage::MsgLogin *data =
		(struct NetworkMessage::MsgLogin *) msg.getData();
	struct NetworkMessage::Header respHeader;
	respHeader.from = 0;
	respHeader.to = this->id;
	try {
		if (this->client.getLoggedIn() ||
			this->server.clientExistsByName(
				std::string(&data->name[0])))
			throw std::logic_error("Client already exists");
			std::cout << "Aftr" << std::endl;
			respHeader.type = NetworkMessage::Header::MessageType::TYPE_LOGIN;
			this->client.setLoggedIn(true);
			this->client.setName(std::string(&data->name[0]));
			std::cout << "Client " << this->client.getName() << "(" << this->id << ") logged in" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Err" << std::endl;
		respHeader.type =
			NetworkMessage::Header::MessageType::TYPE_ERROR;
	}
	NetworkMessage respMsg(respHeader);
	this->sendMessage(respMsg);
}

void NetworkClient::handleMsgLogout(NetworkMessage &msg) noexcept
{
	struct NetworkMessage::Header respHeader;
	respHeader.from = 0;
	respHeader.to = this->id;
	if (!this->client.getLoggedIn())
		respHeader.type = NetworkMessage::Header::MessageType::TYPE_ERROR;
	else {
		respHeader.type = NetworkMessage::Header::MessageType::TYPE_LOGOUT;
		this->client.setLoggedIn(false);
		std::cout << "Client " << this->client.getName() << "(" << this->id << ") logged out" << std::endl;
	}
	NetworkMessage respMsg(respHeader);
	this->sendMessage(respMsg);
}

unsigned long long int NetworkClient::getId() const noexcept
{
	return (this->id);
}

boost::asio::ip::tcp::socket &NetworkClient::getSocket() noexcept
{
	return (this->socket);
}

Client &NetworkClient::getClient() noexcept
{
	return (this->client);
}