/*
** EPITECH PROJECT, 2018
** Client
** File description:
** ClientVoice
*/

#ifndef CLIENTVOICE_HPP_
	#define CLIENTVOICE_HPP_

#include <boost/asio.hpp>
#include "IVoiceStream.hpp"

class ClientVoice : public IVoiceStream {
	public:

	/// \brief
	/// Constructor of the class ClientVoice
	/// \param None
	ClientVoice(const std::string &addr, uint16_t port);

	/// \brief
	/// Constructor of the class ClientVoice
	/// \param None
	ClientVoice();

	/// \brief
	/// Destructor of the class ClientVoice
	/// \param None
	~ClientVoice();

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
	void writeData(
		const unsigned char *data, size_t sz) noexcept;

	private:
	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint *endpoint;
	std::function<void(unsigned char *, size_t)> readCallback;
	bool connected = false;
	unsigned char readBuffer[8192];

	/// \brief
	/// Handler function used to read data
	/// \param error : Error code from boost if something happens
	/// \param nbytes : Number of bytes to read
	/// \return The decoded data
	void handleRead(
		const boost::system::error_code &error, size_t nbytes) noexcept;

	/// \brief
	/// Handler function used to write data
	/// \param err : Error code from boost if something happens
	void handleWrite(const boost::system::error_code &err) noexcept;
};

#endif /* !CLIENTVOICE_HPP_ */
