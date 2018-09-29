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
	void handleReadHeader(
		const boost::system::error_code& err, size_t bytes_transferred);
	void handleReadData(
		const boost::system::error_code& err, size_t bytes_transferred);
	void handleWrite(
		const boost::system::error_code &err) noexcept;
	void sendMessage(NetworkMessage &msg) noexcept;
	void disconnect(const std::string &reason) noexcept;
	void handleMsgError(NetworkMessage &msg) const noexcept;
	void handleMsgLogin(NetworkMessage &msg) noexcept;
	void handleMsgLogout(NetworkMessage &msg) noexcept;
	void handleMsgCall(NetworkMessage &msg) noexcept;
	void handleMsgHangup(NetworkMessage &msg) noexcept;
	void broadcastMsg(NetworkMessage &msg) const noexcept;
	unsigned long long int getId() const noexcept;
	boost::asio::ip::tcp::socket &getSocket() noexcept;
	Client &getClient() noexcept;

	private:
	std::unordered_map<
		unsigned char,
		std::function<void(NetworkMessage &)>> msgMap;
	unsigned long long int id;
	boost::asio::ip::tcp::socket socket;
	NetworkMessage msg;
	unsigned char readData[8192];
	Client client;
	Server &server;
};

#endif /* !NetworkClient_HPP_ */
