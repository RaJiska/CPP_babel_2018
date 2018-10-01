/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Server
*/

#include <iostream>
#include <boost/bind.hpp>
#include "Server.hpp"

Server::Server(unsigned short port) :
	acceptor(this->io_service,
		boost::asio::ip::tcp::endpoint(
			boost::asio::ip::tcp::v4(), port))
{
	this->startAccept();
}

Server::~Server()
{
}

void Server::run()
{
	this->io_service.run();
}

void Server::startAccept()
{
	static unsigned long long int id = 0;
	boost::shared_ptr<NetworkClient> client(
		new NetworkClient(*this, ++id, this->io_service));

	this->acceptor.async_accept(client->getSocket(), boost::bind(
		&Server::handleAccept,
		this,
		client,
		boost::asio::placeholders::error));
}

void Server::handleAccept(
	boost::shared_ptr<NetworkClient> netClient,
	const boost::system::error_code &error)
{
	if (!error) {
		this->clients.push_back(netClient);
		std::cout << "Client " << netClient->getId() <<
			" connected" << std::endl;
		netClient->start();
	}
	this->startAccept();
}

void Server::cleanClosedPeers() noexcept
{
	auto it = std::find_if(
		this->clients.begin(),
		this->clients.end(),
		[] (boost::shared_ptr<NetworkClient> c) {
			return (!c->getSocket().is_open() ||
				!c->getClient().getConnected());
		});
	while (it != this->clients.end()) {
		this->clients.erase(it);
		it = std::find_if(
			this->clients.begin(),
			this->clients.end(),
			[] (boost::shared_ptr<NetworkClient> c) {
				return (!c->getSocket().is_open() ||
					!c->getClient().getConnected());
			});
	}
}

boost::shared_ptr<NetworkClient> Server::clientById(unsigned long long int id)
{
	for (auto it : this->clients) {
		if (it->getId() == id)
			return (it);
	}
	throw std::out_of_range("ID Not in list");
}

boost::shared_ptr<NetworkClient> Server::clientByName(const std::string &name)
{
	for (auto it : this->clients) {
		if (it->getClient().getName() == name)
			return (it);
	}
	throw std::out_of_range("ID Not in list");
}

bool Server::clientExistsByName(const std::string &name) const noexcept
{
	for (auto it : this->clients) {
		if (it->getClient().getLoggedIn() &&
			it->getClient().getName() == name) {
			return (true);
		}
	}
	return (false);
}

bool Server::clientExistsById(unsigned long long int id) const noexcept
{
	for (auto it : this->clients) {
		if (it->getClient().getLoggedIn() &&
			it->getId() == id) {
			return (true);
		}
	}
	return (false);
}

std::vector<boost::shared_ptr<NetworkClient>> &Server::getClients() noexcept
{
	return (this->clients);
}

void Server::sendLol()
{
	/*
	std::cout << "Send" << std::endl;
	struct NetworkMessage::Header header;
	std::memset(&header, 0, sizeof(struct NetworkMessage::Header));
	header.to = 1;
	header.from = 1;
	header.type = NetworkMessage::Header::MessageType::TYPE_CALL;
	header.size = sizeof(struct NetworkMessage::MsgCall);
	NetworkMessage msg(header);
	struct NetworkMessage::MsgLogin a;
	std::memset(&a, 0, sizeof(struct NetworkMessage::MsgLogin));
	a.id = 0;
	std::strcpy(&a.name[0], "Hello");
	msg.setData((unsigned char *) &a, sizeof(struct NetworkMessage::MsgLogin));
	for (auto it : this->clients) {
		it->sendMessage(msg);
	}
	*/
}