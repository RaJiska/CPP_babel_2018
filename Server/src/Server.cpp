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
		new NetworkClient(id++, this->io_service));

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
			return (!c->getSocket().is_open());
		});
	while (it != this->clients.end()) {
		this->clients.erase(it);
		it = std::find_if(
			this->clients.begin(),
			this->clients.end(),
			[] (boost::shared_ptr<NetworkClient> c) {
				return (c->getSocket().is_open());
			});
	}
}

void Server::sendLol()
{
	std::cout << "Send" << std::endl;
	NetworkMessageHeader header;
	header.setFrom(5);
	header.setTo(10);
	NetworkMessage msg(header);
	for (auto it : this->clients) {
		it->sendData(msg);
	}
}