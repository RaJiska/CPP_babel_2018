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

NetworkClient::NetworkClient(unsigned long long int id,
	boost::asio::io_service &service) : id(id), socket(service)
{
}

NetworkClient::~NetworkClient()
{
}

void NetworkClient::start()
{
	/*
	this->socket.read_some(boost::asio::buffer(memset(&this->readData[0], 0, 8192), sizeof(NetworkMessage::Header)));
	struct NetworkMessage::Header *header = (struct NetworkMessage::Header *) &this->readData[0];
	this->socket.read_some(boost::asio::buffer(memset(&this->readData[0], 0, 8192), header->size));
	std::string str((char *) &this->readData[0]);
	std::stringstream ss;
	ss << str;
	boost::archive::text_iarchive ia(ss);
	//NetworkMessage msg;
	//ia >> msg;
	// DO SMTHING
	*/
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

void NetworkClient::sendMessage(NetworkMessage &msg) noexcept
{
	/*
	std::vector<boost::asio::const_buffer> buffers(2);
	std::stringstream ss;
	boost::archive::text_oarchive oa(ss);
	oa << msg;
	std::cout << "Sending: " << ss.str() << std::endl;
	msg.getHeader().size = ss.str().size();
	boost::asio::async_write(this->socket, boost::asio::buffer(boost::asio::buffer(&msg.getHeader(), sizeof(msg.getHeader()))),
		boost::bind(&NetworkClient::handleWrite, this,
			boost::asio::placeholders::error));
	boost::asio::async_write(this->socket, boost::asio::buffer(ss.str()),
		boost::bind(&NetworkClient::handleWrite, this,
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