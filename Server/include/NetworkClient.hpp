/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

#ifndef NetworkClient_HPP_
	#define NetworkClient_HPP_

#include <boost/asio.hpp>

class NetworkClient {
	public:
	NetworkClient(unsigned long long int id, boost::asio::io_service &service);
	NetworkClient(const NetworkClient &client);
	virtual ~NetworkClient();

	boost::asio::ip::tcp::socket &getSocket() noexcept;

	private:
	unsigned long long int id;
	boost::asio::ip::tcp::socket socket;
};

#endif /* !NetworkClient_HPP_ */
