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

/// \file NetworkClient
/// \brief Include file, defines a NetworkClient

class Server;

class NetworkClient {
	public:

	/// \brief
	/// Constructor of the class NetworkClient
	/// \param server : Reference to the server
	/// \param id : The Client's ID
	/// \param service : The socket to be used
	/// \return this->loggedIn : the Client's current state
	NetworkClient(
		Server &server,
		unsigned long long int id, boost::asio::io_service &service);

	/// \brief
	/// Destructor of the class NetworkClient
	/// \param None
	virtual ~NetworkClient();

	/// \brief
	/// Starts the NetworkClient
	/// \param None
	void start();

	/// \brief
	/// Reads and set the header from the received data
	/// \param err : Error code from boost if something happens
	/// \param bytes_transferred : Amount of bytes already readed
	void handleReadHeader(
		const boost::system::error_code &err, size_t bytes_transferred);

	/// \brief
	/// Reads and set the data from the received data
	/// \param err : Error code from boost if something happens
	/// \param bytes_transferred : Amount of bytes already readed
	void handleReadData(
		const boost::system::error_code &err, size_t bytes_transferred);

	/// \brief
	/// Handler function used to write data
	/// \param err : Error code from boost if something happens
	void handleWrite(
		const boost::system::error_code &err) noexcept;

	/// \brief
	/// Sends a NetworkMessage
	/// \param msg : the NetworkMessage to be sent
	void sendMessage(NetworkMessage &msg, bool noHeader = false) noexcept;

	/// \brief
	/// Disconnect the current NetworkClient
	/// \param reason : Why it disconnected
	void disconnect(const std::string &reason) noexcept;

	/// \brief
	/// Handler function used to handle an error
	/// while reading from the socket
	/// \param err : Error code from boost if something happens
	void handleMsgError(NetworkMessage &msg) const noexcept;

	/// \brief
	/// Handler function used when an user tries to log in
	/// \param msg : the NetworkMessage the client sent to log in
	void handleMsgLogin(NetworkMessage &msg) noexcept;

	/// \brief
	/// Handler function used when an user tries to log out
	/// \param msg : the NetworkMessage the client sent to log out
	void handleMsgLogout(NetworkMessage &msg) noexcept;

	/// \brief
	/// Handler function used when an user tries to make a call
	/// \param msg : the NetworkMessage the client sent to make a call
	void handleMsgCall(NetworkMessage &msg) noexcept;

	/// \brief
	/// Handler function used when an user tries to end the call
	/// \param msg : the NetworkMessage the client sent to end the call
	void handleMsgHangup(NetworkMessage &msg) noexcept;

	/// \brief
	/// Handler function used when an user tries to query a user
	/// \param msg : the NetworkMessage the client sent to query
	void handleMsgQuery(NetworkMessage &msg) noexcept;

	/// \brief
	/// Handler function used when an user tries to send a voice packet
	/// \param msg : the NetworkMessage the client sent to get the voice
	void handleMsgVoice(NetworkMessage &msg) noexcept;

	/// \brief
	/// Sends the message to all logged in users
	/// \param msg : the NetworkMessage to be propaged
	void broadcastMsg(NetworkMessage &msg) const noexcept;

	/// \brief
	/// Gets the NetworkClient's ID
	/// \param None
	/// \return The ID of the NetworkClient
	unsigned long long int getId() const noexcept;

	/// \brief
	/// Gets the Client's current socket
	/// \param None
	/// \return A reference to this->socket
	boost::asio::ip::tcp::socket &getSocket() noexcept;

	/// \brief
	/// Gets the Client
	/// \param None
	/// \return A reference to this->client
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
