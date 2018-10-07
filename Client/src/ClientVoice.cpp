/*
** EPITECH PROJECT, 2018
** Client
** File description:
** ClientVoice
*/

#include "ClientVoice.hpp"

ClientVoice::ClientVoice(const std::string &addr, uint16_t port) :
	IVoiceStream(), socket(this->io_service)
{
	this->endpoint = new boost::asio::ip::udp::endpoint(
		boost::asio::ip::address::from_string(addr), port);
	socket.open(boost::asio::ip::udp::v4());
	this->socket.async_receive_from(
		boost::asio::buffer(this->readBuffer, 8192), *this->endpoint,
		boost::bind(&ClientVoice::handleRead, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	this->socket.async_send_to(boost::asio::buffer(std::string("START"), 5),
		*this->endpoint, boost::bind(&ClientVoice::handleWrite, this,
			boost::asio::placeholders::error));
}

ClientVoice::~ClientVoice()
{
	this->socket.close();
}

void ClientVoice::start() noexcept
{
	this->socket.async_send_to(boost::asio::buffer("END"),
		*this->endpoint, boost::bind(&ClientVoice::handleWrite, this,
			boost::asio::placeholders::error));
	this->io_service.run();
}

void ClientVoice::setReadCallback(
	std::function<void(unsigned char *, size_t)> f) noexcept
{
	this->readCallback = f;
}

void ClientVoice::writeData(
	const unsigned char *data, size_t sz) noexcept
{
	if (this->connected)
		this->socket.async_send_to(boost::asio::buffer(data, sz),
		*this->endpoint, boost::bind(&ClientVoice::handleWrite, this,
			boost::asio::placeholders::error));
}

void ClientVoice::handleRead(
	const boost::system::error_code &error, size_t nbytes) noexcept
{
	if (!this->connected && nbytes >= 5 && !memcmp(this->readBuffer, "START", 5))
		this->connected = true;
	else if (this->connected && nbytes >= 3 && !memcmp(this->readBuffer, "END", 3))
		this->connected = false;
	else {

	}
}

void ClientVoice::handleWrite(const boost::system::error_code &err) noexcept
{
}
