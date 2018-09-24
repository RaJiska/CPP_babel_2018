/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

#ifndef NetworkClient_HPP_
	#define NetworkClient_HPP_

#include <boost/asio.hpp>
#include "Client.hpp"
#include "NetworkMessage.hpp"

class NetworkClient {
	public:
	NetworkClient(unsigned long long int id, boost::asio::io_service &service);
	virtual ~NetworkClient();

	void start();
	void handleRead(
		const boost::system::error_code &err, size_t bytesNb) noexcept;
	void handleWrite(
		const boost::system::error_code &err) noexcept;
	void sendData(const NetworkMessage &msg);
	void disconnect(const std::string &reason) noexcept;
	unsigned long long int getId() const noexcept;
	boost::asio::ip::tcp::socket &getSocket() noexcept;

	private:
	unsigned long long int id;
	boost::asio::ip::tcp::socket socket;
	unsigned char readData[8192];
	NetworkMessage readMessage;
	Client client;
	std::vector<boost::asio::const_buffer> buffers;
};

#endif /* !NetworkClient_HPP_ */
