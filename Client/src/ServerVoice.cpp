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
	this->socket.async_receive_from(
		boost::asio::buffer(this->readBuffer, 8192), endpoint,
		boost::bind(&ServerVoice::handleRead, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	this->socket.async_send_to(boost::asio::buffer("START"),
		endpoint, boost::bind(&ServerVoice::handleWrite, this,
			boost::asio::placeholders::error));
}

ServerVoice::~ServerVoice()
{
	this->socket.async_send_to(boost::asio::buffer("END"),
		endpoint, boost::bind(&ServerVoice::handleWrite, this,
			boost::asio::placeholders::error));
	this->socket.close();
}

void ServerVoice::start() noexcept
{
	this->io_service.run();
}

void ServerVoice::setReadCallback(
	std::function<void(unsigned char *, size_t)> f) noexcept
{
	this->readCallback = f;
}

void ServerVoice::writeData(const unsigned char *data, size_t sz) noexcept
{
	if (this->connected)
		this->socket.async_send_to(boost::asio::buffer(data, sz),
			endpoint, boost::bind(&ServerVoice::handleWrite, this,
				boost::asio::placeholders::error));
}

void ServerVoice::handleRead(
	const boost::system::error_code &err, size_t nbytes) noexcept
{
	if (!this->connected && nbytes >= 5 && !memcmp(this->readBuffer, "START", 5))
		this->connected = true;
	else if (this->connected && nbytes >= 3 && !memcmp(this->readBuffer, "END", 3))
		this->connected = false;
	else {
		/* Handle DATA to be read */
	}
}

void ServerVoice::handleWrite(const boost::system::error_code &err) noexcept
{
}