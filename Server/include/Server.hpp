/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Server
*/

#ifndef SERVER_HPP_
	#define SERVER_HPP_

#include <boost/asio.hpp>
#include "NetworkClient.hpp"

class Server {
	public:
	Server(unsigned short port);
	virtual ~Server();

	private:
	void startAccept();
	void handleAccept(
		boost::shared_ptr<NetworkClient> client,
		const boost::system::error_code &error);

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::acceptor acceptor;
	std::vector<boost::shared_ptr<NetworkClient>> clients;
};

#endif /* !SERVER_HPP_ */
