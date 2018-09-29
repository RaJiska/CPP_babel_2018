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

class NetworkClient;
class NetworkMessage;

class Server {
	public:
	Server(unsigned short port);
	virtual ~Server();

	void run();
	void cleanClosedPeers() noexcept;
	boost::shared_ptr<NetworkClient> clientById(unsigned long long int id);
	boost::shared_ptr<NetworkClient> clientByName(const std::string &name);
	bool clientExistsByName(const std::string &name) const noexcept;
	void sendLol();

	private:
	void startAccept();
	void handleAccept(
		boost::shared_ptr<NetworkClient> netClient,
		const boost::system::error_code &error);

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::acceptor acceptor;
	std::vector<boost::shared_ptr<NetworkClient>> clients;
};

#endif /* !SERVER_HPP_ */
