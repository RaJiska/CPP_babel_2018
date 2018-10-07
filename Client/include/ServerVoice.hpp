/*
** EPITECH PROJECT, 2018
** Server
** File description:
** ServerVoice
*/

#ifndef SERVERVOICE_HPP_
	#define SERVERVOICE_HPP_

#include <boost/asio.hpp>

class ServerVoice {
	public:
	ServerVoice(uint16_t port);
	~ServerVoice();

	void handleRead(const boost::system::error_code &error,
		size_t nbytes) noexcept;
	void writeData(const unsigned char *data, size_t sz) noexcept;
	void handleWrite(const boost::system::error_code &err) noexcept;

	private:
	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint endpoint;
	bool connected = false;
	unsigned char readBuffer[8192];
};

#endif /* !SERVERVOICE_HPP_ */
