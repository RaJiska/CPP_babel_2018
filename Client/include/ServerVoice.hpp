/*
** EPITECH PROJECT, 2018
** Server
** File description:
** ServerVoice
*/

#ifndef SERVERVOICE_HPP_
	#define SERVERVOICE_HPP_

#include <boost/asio.hpp>
#include "IVoiceStream.hpp"

class ServerVoice : public IVoiceStream {
	public:

	/// \brief
	/// Constructor of the class ServerVoice
	/// \param None
	ServerVoice(uint16_t port);

	/// \brief
	/// Destructor of the class ClientVoice
	/// \param None
	~ServerVoice();

	/// \brief
	/// Starts the io_service
	/// \param None
	void start() noexcept;

	/// \brief
	/// Connects to a specified server
	/// \param addr : server's address
	/// \param port : server's port
	void connect(const std::string &addr, uint16_t port) noexcept;

	/// \brief
	/// Disconnects from the current server
	void disconnect() noexcept;

	/// \brief
	/// Sets the read callback function to the specified one
	/// \param f : the new read callback function
	void setReadCallback(
		std::function<void(unsigned char *, size_t)> f) noexcept;

	/// \brief
	/// Function used to write data of size sz
	/// \param data : Buffer to write
	/// \param sz : Buffer's size
	void writeData(const unsigned char *data, size_t sz) noexcept;

	private:
	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint endpoint;
	bool connected = false;
	unsigned char readBuffer[8192];
	std::function<void(unsigned char *, size_t)> readCallback;

	/// \brief
	/// Handler function used to read data
	/// \param error : Error code from boost if something happens
	/// \param nbytes : Number of bytes to read
	void handleRead(
		const boost::system::error_code &error, size_t nbytes) noexcept;

	/// \brief
	/// Handler function used to write data
	/// \param err : Error code from boost if something happens
	void handleWrite(const boost::system::error_code &err) noexcept;
};

#endif /* !SERVERVOICE_HPP_ */
