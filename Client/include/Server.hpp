/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Server
*/

#ifndef SERVER_HPP_
	#define SERVER_HPP_

#include <QtNetwork>
#include "NetworkMessage.hpp"

class Server {
	public:
	Server(const std::string &address, uint16_t port);
	~Server();

	bool sendLoginMsg(const std::string &name) noexcept;

	private:
	void sendMessage(NetworkMessage &msg) noexcept;
	void readMessage(NetworkMessage &msg) noexcept;
	void readNBytes(QByteArray &arr, qint64 nBytes) noexcept;

	QTcpSocket socket;
	unsigned long long int clientId;
	NetworkMessage response;
};

#endif /* !SERVER_HPP_ */
