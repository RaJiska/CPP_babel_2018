/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

#ifndef NETCLIENT_HPP_
	#define NETCLIENT_HPP_

#include <boost/asio.hpp>

class NetClient {
	public:
	NetClient(unsigned long long int id, boost::asio::io_service &service);
	virtual ~NetClient();

	boost::asio::ip::tcp::socket &getSocket() noexcept;

	private:
	unsigned long long int id;
	boost::asio::ip::tcp::socket socket;
};

#endif /* !NETCLIENT_HPP_ */
