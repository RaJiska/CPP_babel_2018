/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Server
*/

#ifndef SERVER_HPP_
	#define SERVER_HPP_

#include <boost/asio.hpp>
#include <unordered_map>
#include "NetworkMessage.hpp"

class Server {
	public:
	struct Client
	{
		unsigned long long int id;
		std::string name;
	};

	Server(const std::string &address, uint16_t port);
	~Server();

	void sendLoginMsg(const std::string &name) noexcept;
	void handleLoginMsg(NetworkMessage msg) noexcept;
	void sendLogoutMsg() noexcept;
	void handleLogoutMsg(NetworkMessage msg) noexcept;
	void sendCallMsg(unsigned long long int target) noexcept;
	void handleCallMsg(NetworkMessage msg) noexcept;
	void sendHangupMsg(unsigned long long int target) noexcept;
	void handleHangupMsg(NetworkMessage msg) noexcept;
	void sendQueryMsg(unsigned long long int id) noexcept;
	void handleQueryMsg(NetworkMessage msg) noexcept;
	void run() noexcept;

	std::vector<Client> clientsList;

	private:
	void start() noexcept;
	void sendMessage(NetworkMessage &msg) noexcept;
	void handleWrite(const boost::system::error_code &err) noexcept;
	void handleReadHeader(
		const boost::system::error_code &err, size_t bytes_transferred);
	void handleReadData(
		const boost::system::error_code &err, size_t bytes_transferred);

	unsigned long long int clientId;
	NetworkMessage msg;
	std::unordered_map<
		unsigned char,
		std::function<void(NetworkMessage &)>> msgMap;
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket;
	unsigned char readData[8192];
};

#endif /* !SERVER_HPP_ */
