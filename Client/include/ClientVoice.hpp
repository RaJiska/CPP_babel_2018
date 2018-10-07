/*
** EPITECH PROJECT, 2018
** Client
** File description:
** ClientVoice
*/

#ifndef CLIENTVOICE_HPP_
	#define CLIENTVOICE_HPP_

#include <boost/asio.hpp>
#include "IVoiceStream.hpp"

class ClientVoice : public IVoiceStream {
	public:
	ClientVoice(const std::string &addr, uint16_t port);
	ClientVoice();
	~ClientVoice();

	void start() noexcept;
	void connect(const std::string &addr, uint16_t port) noexcept;
	void disconnect() noexcept;
	void setReadCallback(
		std::function<void(unsigned char *, size_t)> f) noexcept;
	void writeData(
		const unsigned char *data, size_t sz) noexcept;

	private:
	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint *endpoint = new boost::asio::ip::udp::endpoint();
	std::function<void(unsigned char *, size_t)> readCallback;
	bool connected = false;
	unsigned char readBuffer[8192];

	void handleRead(
		const boost::system::error_code &error, size_t nbytes) noexcept;
	void handleWrite(const boost::system::error_code &err) noexcept;
};

#endif /* !CLIENTVOICE_HPP_ */
