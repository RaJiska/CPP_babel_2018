/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

#ifndef NetworkClient_HPP_
	#define NetworkClient_HPP_

#include <boost/asio.hpp>
#include <unordered_map>
#include "Server.hpp"
#include "Client.hpp"
#include "NetworkMessage.hpp"

class Server;

class NetworkClient {
	public:
	NetworkClient(
		Server &server,
		unsigned long long int id, boost::asio::io_service &service);
	virtual ~NetworkClient();

	void start();
	void handleWrite(
		const boost::system::error_code &err) noexcept;
	void sendMessage(NetworkMessage &msg) noexcept;
	void disconnect(const std::string &reason) noexcept;
	void handleMsgError(NetworkMessage &msg) const noexcept;
	void handleMsgLogin(NetworkMessage &msg) noexcept;
	void handleMsgLogout(NetworkMessage &msg) noexcept;
	unsigned long long int getId() const noexcept;
	boost::asio::ip::tcp::socket &getSocket() noexcept;
	Client &getClient() noexcept;

	private:
	std::unordered_map<
		unsigned char,
		std::function<void(NetworkMessage &)>> msgMap;
	unsigned long long int id;
	boost::asio::ip::tcp::socket socket;
	unsigned char readData[8192];
	struct NetworkMessage::Header *header =
		(struct NetworkMessage::Header *) &this->readData[0];
	Client client;
	Server &server;
};

#endif /* !NetworkClient_HPP_ */
