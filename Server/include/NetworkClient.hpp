/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

#ifndef NetworkClient_HPP_
	#define NetworkClient_HPP_

#include <boost/asio.hpp>
#include "Client.hpp"

class NetworkClient {
	public:
	NetworkClient(unsigned long long int id, boost::asio::io_service &service);
	virtual ~NetworkClient();

	void start();
	void handleRead(
		const boost::system::error_code &err, size_t bytesNb) noexcept;
	void disconnect(const std::string &reason) noexcept;
	unsigned long long int getId() const noexcept;
	boost::asio::ip::tcp::socket &getSocket() noexcept;

	private:
	unsigned long long int id;
	boost::asio::ip::tcp::socket socket;
	unsigned char data[1024];
	Client client;
};

#endif /* !NetworkClient_HPP_ */
