/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

#ifndef CLIENT_HPP_
	#define CLIENT_HPP_

#include <string>
class Client {
	public:
	Client();
	~Client();

	private:
	bool loggedIn = false;
	std::string name;
};

#endif /* !CLIENT_HPP_ */
