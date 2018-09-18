/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Server
*/

#include <boost/bind.hpp>
#include "Server.hpp"

Server::Server(unsigned short port) :
	acceptor(this->io_service,
		boost::asio::ip::tcp::endpoint(
			boost::asio::ip::tcp::v4(), port))
{
	this->startAccept();
	this->io_service.run();
}

Server::~Server()
{
}

void Server::startAccept()
{
	static unsigned long long int id = 0;
	boost::shared_ptr<NetClient> client(
		new NetClient(id++, this->io_service));

	this->acceptor.async_accept(client->getSocket(), boost::bind(
		&Server::handleAccept,
		this,
		client,
		boost::asio::placeholders::error));
}

void Server::handleAccept(
	boost::shared_ptr<NetClient> client,
	const boost::system::error_code &error)
{
	this->startAccept();
}
