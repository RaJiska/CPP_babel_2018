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
#include "mainwindow.h"

class MainWindow;

class Server {
	public:
	struct Client
	{
		unsigned long long int id;
		std::string name;
	};

	/// \brief
	/// Constructor of the class Server
	/// \param address : Server's address
	/// \param port : Server's port
	/// \param window : QT's window
	Server(const std::string &address, uint16_t port, MainWindow &window);

	/// \brief
	/// Destructor of the class Server
	~Server();

	/// \brief
	/// Sends the login message
	/// \param name : name of the newly logged user
	void sendLoginMsg(const std::string &name) noexcept;

	/// \brief
	/// Login message function handler
	/// \param msg : The NetworkMessage received
	void handleLoginMsg(NetworkMessage msg) noexcept;

	/// \brief
	/// Sends the logout message
	void sendLogoutMsg() noexcept;

	/// \brief
	/// Logout message function handler
	/// \param msg : The NetworkMessage received
	void handleLogoutMsg(NetworkMessage msg) noexcept;

	/// \brief
	/// Sends the call message
	/// \param name target : Who is going to be called
	void sendCallMsg(unsigned long long int target) noexcept;

	/// \brief
	/// Call message function handler
	/// \param msg : The NetworkMessage received
	void handleCallMsg(NetworkMessage msg) noexcept;

	/// \brief
	/// Sends the hangup message
	/// \param name target : Who is going to be hanged up
	void sendHangupMsg(unsigned long long int target) noexcept;

	/// \brief
	/// Hangup message function handler
	/// \param msg : The NetworkMessage received
	void handleHangupMsg(NetworkMessage msg) noexcept;

	/// \brief
	/// Sends the query message
	/// \param name : name of the newly logged user
	void sendQueryMsg(const std::string &name) noexcept;

	/// \brief
	/// Query message function handler
	/// \param name : name of the newly logged user
	void handleQueryMsg(NetworkMessage msg) noexcept;

	/// \brief
	/// Starts the io_service
	void run() noexcept;

	std::vector<Client> clientsList;
	boost::asio::io_service io_service;

	private:
	void start() noexcept;
	void sendMessage(NetworkMessage &msg) noexcept;
	void handleWrite(const boost::system::error_code &err) noexcept;

	/// \brief
	/// Handler function used to read the header's data
	/// \param err : Error code from boost if something happens
	/// \param bytes_transferred : Number of bytes to read
	void handleReadHeader(
		const boost::system::error_code &err, size_t bytes_transferred);

	/// \brief
	/// Handler function used to read the data
	/// \param err : Error code from boost if something happens
	/// \param bytes_transferred : Number of bytes to read
	void handleReadData(
		const boost::system::error_code &err, size_t bytes_transferred);

	unsigned long long int clientId;
	NetworkMessage msg;
	std::unordered_map<
		unsigned char,
		std::function<void(NetworkMessage &)>> msgMap;
	boost::asio::ip::tcp::socket socket;
	unsigned char readData[8192];
	MainWindow &window;
};

#endif /* !SERVER_HPP_ */
