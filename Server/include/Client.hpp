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

	void setLoggedIn(bool loggedIn) noexcept;
	bool getLoggedIn() const noexcept;
	void setName(const std::string &name) noexcept;
	const std::string &getName() const noexcept;
	void setConnected(bool connected) noexcept;
	bool getConnected() const noexcept;

	private:
	bool connected = true;
	bool loggedIn = false;
	std::string name;
};

#endif /* !CLIENT_HPP_ */
