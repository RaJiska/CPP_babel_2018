/*
** EPITECH PROJECT, 2018
** Server
** File description:
** ServerVoice
*/

#ifndef SERVERVOICE_HPP_
	#define SERVERVOICE_HPP_

#include <boost/asio.hpp>
#include "IVoiceStream.hpp"

class ServerVoice : public IVoiceStream {
	public:
	ServerVoice(uint16_t port);
	~ServerVoice();

	void start() noexcept;
	void connect(const std::string &addr, uint16_t port) noexcept;
	void disconnected() noexcept;
	void setReadCallback(
		std::function<void(unsigned char *, size_t)> f) noexcept;
	void writeData(const unsigned char *data, size_t sz) noexcept;

	private:
	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint endpoint;
	bool connected = false;
	unsigned char readBuffer[8192];
	std::function<void(unsigned char *, size_t)> readCallback;

	void handleRead(
		const boost::system::error_code &error, size_t nbytes) noexcept;
	void handleWrite(const boost::system::error_code &err) noexcept;
};

#endif /* !SERVERVOICE_HPP_ */
