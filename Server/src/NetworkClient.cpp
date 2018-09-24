/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream> // DBG
#include "NetworkClient.hpp"

NetworkClient::NetworkClient(unsigned long long int id,
	boost::asio::io_service &service) : id(id), socket(service)
{
}

NetworkClient::~NetworkClient()
{
}

void NetworkClient::start()
{
	this->socket.async_read_some(
		boost::asio::buffer(this->readData, sizeof(this->readData)),
		boost::bind(&NetworkClient::handleRead, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void NetworkClient::handleRead(
	const boost::system::error_code &err, size_t bytesNb) noexcept
{
	if (!err) {
		this->start();
	}
	else
		this->disconnect(err.message());
}

void NetworkClient::sendData(const NetworkMessage &msg)
{
	/*
	std::stringstream ss;
	boost::archive::text_oarchive ar(ss);

	ar << msg;
	buffers.push_back(boost::asio::buffer(oss.str()));
	boost::asio::async_write(this->socket, buffers, boost::bind(&NetworkClient::handleWrite, this,
			boost::asio::placeholders::error));
	*/
}

void NetworkClient::handleWrite(
	const boost::system::error_code &err) noexcept
{

}

void NetworkClient::disconnect(const std::string &reason) noexcept
{
	std::cout << "Client " << this->id <<
		" disconnected: " << reason << std::endl;
	this->socket.close();
}

unsigned long long int NetworkClient::getId() const noexcept
{
	return (this->id);
}

boost::asio::ip::tcp::socket &NetworkClient::getSocket() noexcept
{
	return (this->socket);
}