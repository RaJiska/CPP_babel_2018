/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include "NetworkClient.hpp"

NetworkClient::NetworkClient(Server &server,
	unsigned long long int id, boost::asio::io_service &service) :
	server(server), id(id), socket(service)
{
	this->msgMap[NetworkMessage::Header::TYPE_ERROR] =
	std::bind(&NetworkClient::handleMsgError, this, std::placeholders::_1);
	this->msgMap[NetworkMessage::Header::TYPE_LOGIN] =
	std::bind(&NetworkClient::handleMsgLogin, this, std::placeholders::_1);
	this->msgMap[NetworkMessage::Header::TYPE_LOGOUT] =
	std::bind(&NetworkClient::handleMsgLogout, this, std::placeholders::_1);
	this->msgMap[NetworkMessage::Header::TYPE_CALL] =
	std::bind(&NetworkClient::handleMsgCall, this, std::placeholders::_1);
	this->msgMap[NetworkMessage::Header::TYPE_HANGUP] =
	std::bind(&NetworkClient::handleMsgHangup, this, std::placeholders::_1);
	this->msgMap[NetworkMessage::Header::TYPE_QUERY] =
	std::bind(&NetworkClient::handleMsgQuery, this, std::placeholders::_1);
}

NetworkClient::~NetworkClient()
{
}

void NetworkClient::start()
{
	this->socket.async_read_some(
		boost::asio::buffer(memset(&this->readData[0], 0, 8192),
			sizeof(NetworkMessage::Header)),
		boost::bind(&NetworkClient::handleReadHeader, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void NetworkClient::handleReadHeader(
	const boost::system::error_code &err, size_t bytes_transferred)
{
	if (err)
		this->disconnect(err.message());
	else {
		std::memcpy(&this->msg.getHeader(), &this->readData[0],
			sizeof(NetworkMessage::Header));
		this->socket.async_read_some(
			boost::asio::buffer(memset(&this->readData[0], 0, 8192),
				this->msg.getHeader().size),
			boost::bind(&NetworkClient::handleReadData, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}
}

void NetworkClient::handleReadData(
	const boost::system::error_code &err, size_t bytes_transferred)
{
	if (err)
		this->disconnect(std::to_string(err.value()) + err.message());
	else {
		this->msg.setData(this->readData, this->msg.getHeader().size);
		try {
			this->msgMap[this->msg.getHeader().type](msg);
		}
		catch (std::exception &e) {
		}
		this->start();
	}
}

void NetworkClient::sendMessage(NetworkMessage &msg, bool noHeader)
	noexcept
{
	if (!noHeader)
		boost::asio::async_write(this->socket, boost::asio::buffer(
		boost::asio::buffer(&msg.getHeader(), sizeof(msg.getHeader()))),
		boost::bind(&NetworkClient::handleWrite, this,
		boost::asio::placeholders::error));
	boost::asio::async_write(this->socket, boost::asio::buffer(
		boost::asio::buffer(msg.getData(), msg.getHeader().size)),
		boost::bind(&NetworkClient::handleWrite, this,
			boost::asio::placeholders::error));
}

void NetworkClient::handleWrite(
	const boost::system::error_code &err) noexcept
{
}

void NetworkClient::disconnect(const std::string &reason) noexcept
{
	std::cout << "Client " << this->id <<
		" disconnected: " << reason << std::endl;
	this->client.setConnected(false);
	this->server.cleanClosedPeers();
}

void NetworkClient::handleMsgError(NetworkMessage &msg) const noexcept
{
}

void NetworkClient::handleMsgLogin(NetworkMessage &msg) noexcept
{
	struct NetworkMessage::MsgLogin *data =
		(struct NetworkMessage::MsgLogin *) msg.getData();
	struct NetworkMessage::Header rHeader = { this->id, this->id,
			NetworkMessage::Header::MessageType::TYPE_ERROR, 0 };
	try {
		if (this->client.getLoggedIn() ||
			this->server.clientExistsByName(
				std::string(&data->name[0])))
			throw std::logic_error("Client already exists");
		this->client.setLoggedIn(true);
		this->client.setName(std::string(&data->name[0]));
		std::cout << "Client " << this->client.getName()
			<< " (" << this->id << ") logged in" << std::endl;
		rHeader.type = NetworkMessage::Header::MessageType::TYPE_LOGIN;
		rHeader.size = sizeof(struct NetworkMessage::MsgLogin);
		this->sendMessage(msg);
	}
	catch (std::exception &e) {
		NetworkMessage rMsg(rHeader);
		this->sendMessage(rMsg);
	}
}

void NetworkClient::handleMsgLogout(NetworkMessage &msg) noexcept
{
	struct NetworkMessage::Header rHeader;
	rHeader.from = this->id;
	rHeader.to = this->id;
	if (!this->client.getLoggedIn()) {
		rHeader.type = NetworkMessage::Header::MessageType::TYPE_ERROR;
	}
	else {
		rHeader.type = NetworkMessage::Header::MessageType::TYPE_LOGOUT;
		this->client.setLoggedIn(false);
		std::cout << "Client " << this->client.getName() << " ("
			<< this->id << ") logged out" << std::endl;
	}
	rHeader.size = 0;
	NetworkMessage rMsg(rHeader);
	this->sendMessage(rMsg);
}

void NetworkClient::handleMsgCall(NetworkMessage &msg) noexcept
{
	struct NetworkMessage::Header respHeader;
	struct NetworkMessage::MsgCall *data =
		(struct NetworkMessage::MsgCall *) msg.getData();
	std::memset(data, 0, sizeof(struct NetworkMessage::MsgCall));
	if (!this->client.getLoggedIn() ||
		!this->server.clientExistsById(msg.getHeader().to)) {
		respHeader.from = 0;
		respHeader.to = this->id;
		respHeader.type =
			NetworkMessage::Header::MessageType::TYPE_ERROR;
	}
	else {
		std::strcpy(&data->address[0], this->socket.remote_endpoint().
			address().to_string().c_str());
		respHeader.from = this->id;
		respHeader.to = msg.getHeader().to;
		respHeader.type =
			NetworkMessage::Header::MessageType::TYPE_CALL;
	}
	std::cout << "Sending: '" << data->address << "'" << std::endl;
	respHeader.size = sizeof(struct NetworkMessage::MsgCall);
	msg.setHeader(respHeader);
	this->server.clientById(msg.getHeader().to)->sendMessage(msg);
}

void NetworkClient::handleMsgHangup(NetworkMessage &msg) noexcept
{
	struct NetworkMessage::Header respHeader;
	if (!this->client.getLoggedIn()) {
		respHeader.from = 0;
		respHeader.to = this->id;
		respHeader.type =
			NetworkMessage::Header::MessageType::TYPE_ERROR;
	}
	else {
		respHeader.from = this->id;
		respHeader.to = msg.getHeader().to;
		respHeader.type =
			NetworkMessage::Header::MessageType::TYPE_HANGUP;
	}
	respHeader.size = 0;
	NetworkMessage respMsg(respHeader);
	this->sendMessage(respMsg);
}

void NetworkClient::handleMsgQuery(NetworkMessage &msg) noexcept
{
	struct NetworkMessage::Header respHeader;
	struct NetworkMessage::MsgQuery *data =
		(struct NetworkMessage::MsgQuery *) msg.getData();
	respHeader.from = 0;
	respHeader.to = this->id;
	respHeader.type = NetworkMessage::Header::TYPE_QUERY;
	respHeader.size = sizeof(struct NetworkMessage::MsgQuery);
	if (!this->server.clientExistsById(data->id))
		data->id = 0;
	else {
		std::strncpy(data->name,
			this->server.clientById(
				data->id)->getClient().getName().c_str(),
			31)[31] = 0;
	}
	NetworkMessage respMsg(msg);
	this->sendMessage(msg);
}

void NetworkClient::handleMsgVoice(NetworkMessage &msg) noexcept
{
	if (this->server.clientExistsById(msg.getHeader().to)) {
		auto client = this->server.clientById(msg.getHeader().to);
		if (client->getClient().getLoggedIn())
			client->sendMessage(msg);
	}
}

void NetworkClient::broadcastMsg(NetworkMessage &msg) const noexcept
{
	for (auto it : this->server.getClients()) {
		if (it->client.getLoggedIn()) {
			msg.getHeader().to = it->getId();
			it->sendMessage(msg);
		}
	}
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