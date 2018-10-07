/*
** EPITECH PROJECT, 2018
** Server$*
** File description:
** ServerVoice
*/

#include "IVoiceStream.hpp"
#include "ServerVoice.hpp"

ServerVoice::ServerVoice(uint16_t port) : IVoiceStream(),
	socket(io_service, boost::asio::ip::udp::endpoint(
		boost::asio::ip::udp::v4(), port))
{
	this->connect("", port);
}

ServerVoice::~ServerVoice()
{
}

void ServerVoice::start() noexcept
{
	std::cout << "ServerVoice::start" << std::endl;
	this->io_service.run();
}

void ServerVoice::connect(
	const std::string &addr, uint16_t port) noexcept
{
	this->socket.async_receive_from(
		boost::asio::buffer(this->readBuffer, 8192), this->endpoint,
		boost::bind(&ServerVoice::handleRead, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void ServerVoice::disconnect() noexcept
{
	this->connected = false;
	this->io_service.stop();
	this->socket.close();
}

void ServerVoice::setReadCallback(
	std::function<void(unsigned char *, size_t)> f) noexcept
{
	this->readCallback = f;
}

void ServerVoice::writeData(const unsigned char *data, size_t sz) noexcept
{
	std::cout << "Srv Write: " << data << std::endl;
	this->socket.async_send_to(boost::asio::buffer(data, sz),
		endpoint, boost::bind(&ServerVoice::handleWrite, this,
			boost::asio::placeholders::error));
}

void ServerVoice::handleRead(
	const boost::system::error_code &err, size_t nbytes) noexcept
{
	std::cout << "Srv Read: " << this->readBuffer << std::endl;
	this->readCallback(this->readBuffer, nbytes);
	this->socket.async_receive_from(
		boost::asio::buffer(this->readBuffer, 8192), this->endpoint,
		boost::bind(&ServerVoice::handleRead, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void ServerVoice::handleWrite(const boost::system::error_code &err) noexcept
{
}