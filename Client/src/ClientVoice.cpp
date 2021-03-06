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
	this->connect(addr, port);
}

ClientVoice::ClientVoice() : IVoiceStream(), socket(this->io_service)
{
}

ClientVoice::~ClientVoice()
{
}

void ClientVoice::start() noexcept
{
	std::cout << "ClientVoice::start" << std::endl;
	this->io_service.run();
}

void ClientVoice::connect(
	const std::string &addr, uint16_t port) noexcept
{
	this->socket.open(boost::asio::ip::udp::v4());
	this->socket.set_option(boost::asio::socket_base::broadcast(true));
	this->endpoint = new boost::asio::ip::udp::endpoint(
		boost::asio::ip::address::from_string(addr), port);
	this->socket.async_receive_from(
		boost::asio::buffer(this->readBuffer, 8192), *this->endpoint,
		boost::bind(&ClientVoice::handleRead, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	std::cout << "Connect" << std::endl;
}

void ClientVoice::disconnect() noexcept
{
	this->socket.async_send_to(boost::asio::buffer("END"),
		*this->endpoint, boost::bind(&ClientVoice::handleWrite, this,
			boost::asio::placeholders::error));
	this->connected = false;
	this->io_service.stop();
	this->socket.close();
}

void ClientVoice::setReadCallback(
	std::function<void(unsigned char *, size_t)> f) noexcept
{
	this->readCallback = f;
}

void ClientVoice::writeData(
	const unsigned char *data, size_t sz) noexcept
{
	std::cout << "Cli Write: " << sz << std::endl;
	this->socket.async_send_to(boost::asio::buffer(data, sz),
	*this->endpoint, boost::bind(&ClientVoice::handleWrite, this,
		boost::asio::placeholders::error));
}

void ClientVoice::handleRead(
	const boost::system::error_code &error, size_t nbytes) noexcept
{
	std::cout << "Cli Read: " << nbytes << std::endl;
	this->readCallback(this->readBuffer, nbytes);
	this->socket.async_receive_from(
		boost::asio::buffer(this->readBuffer, 8192), *this->endpoint,
		boost::bind(&ClientVoice::handleRead, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void ClientVoice::handleWrite(const boost::system::error_code &err) noexcept
{
}
