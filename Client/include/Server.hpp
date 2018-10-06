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
	struct Client
	{
		unsigned long long int id;
		std::string name;
	};

	Server(const std::string &address, uint16_t port);
	~Server();

	NetworkMessage sendLoginMsg(const std::string &name) noexcept;
	NetworkMessage sendLogoutMsg() noexcept;
	void sendCallMsg(unsigned long long int target) noexcept;
	void sendHangupMsg(unsigned long long int target) noexcept;
	void sendListMsg() noexcept;

	private:
	void sendMessage(NetworkMessage &msg) noexcept;
	NetworkMessage readMessage() noexcept;
	void readNBytes(QByteArray &arr, qint64 nBytes) noexcept;

	QTcpSocket socket;
	unsigned long long int clientId;
	NetworkMessage response;
	std::vector<Client> clientsList;
};

#endif /* !SERVER_HPP_ */
