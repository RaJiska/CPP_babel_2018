/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

#ifndef CLIENT_HPP_
	#define CLIENT_HPP_

#include "NetworkClient.hpp"

class Client {
	public:
	Client(NetworkClient &netClient);
	~Client();

	private:
	NetworkClient &netClient;
};

#endif /* !CLIENT_HPP_ */
