/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Server
*/

/// \file Server.hpp
/// \brief Include file for the server

#ifndef SERVER_HPP_
	#define SERVER_HPP_

#include <boost/asio.hpp>
#include "NetworkClient.hpp"

class NetworkClient;
class NetworkMessage;

class Server {
	public:

	/// \brief
	/// Constructor of the class Server
	/// \param port : port the server listen on
	Server(unsigned short port);

	/// \brief
	/// Destructor of the class Server
	/// \param None
	virtual ~Server();

	/// \brief
	/// Starts the server
	/// \param None
	void run();

	/// \brief
	/// Cleans the closed peers
	/// \param None
	void cleanClosedPeers() noexcept;

	/// \brief
	/// Gets a client by ID
	/// \param id : the id of the client to be seeked
	/// \return A boost::shared_ptr of the client corresponding
	boost::shared_ptr<NetworkClient> clientById(unsigned long long int id);

	/// \brief
	/// Gets a client by name
	/// \param name : the name of the client to be seeked
	/// \return A boost::shared_ptr of the client corresponding
	boost::shared_ptr<NetworkClient> clientByName(const std::string &name);

	/// \brief
	/// Checks if the client with the specified name exists
	/// \param name : the name of the client to be seeked
	/// \return A bool set to True if the client exists
	bool clientExistsByName(const std::string &name) const noexcept;

	/// \brief
	/// Checks if the client with the specified ID exists
	/// \param ID : the ID of the client to be seeked
	/// \return A bool set to True if the client exists
	bool clientExistsById(unsigned long long int id) const noexcept;

	/// \brief
	/// Gets all of the clients
	/// \param None
	/// \return a std::vector containing all of the clients
	std::vector<boost::shared_ptr<NetworkClient>> &getClients() noexcept;

	private:

	/// \brief
	/// Starts listening on the socket
	/// \param None
	void startAccept();

	/// \brief
	/// Checks if the client with the specified ID exists
	/// \param netClient : Client
	/// \param error : Error code from Boost if an error occured
	void handleAccept(
		boost::shared_ptr<NetworkClient> netClient,
		const boost::system::error_code &error);

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::acceptor acceptor;
	std::vector<boost::shared_ptr<NetworkClient>> clients;
};

#endif /* !SERVER_HPP_ */
