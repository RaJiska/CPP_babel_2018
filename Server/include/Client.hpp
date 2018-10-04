/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

/// \file Client.hpp
/// \brief Include file, defines a Client
#ifndef CLIENT_HPP_
	#define CLIENT_HPP_

#include <string>
class Client {
	public:

	/// \brief
	/// Constructor of the class Client
	/// \param None
	Client();

	/// \brief
	/// Destructor of the class Client
	/// \param None
	~Client();

	/// \brief
	/// Sets this-> loggedIn to the new value
	/// \param loggedIn : new login status value for the Client
	void setLoggedIn(bool loggedIn) noexcept;

	/// \brief
	/// Gets the Client's current state
	/// \param None
	/// \return this->loggedIn : the Client's current state
	bool getLoggedIn() const noexcept;

	/// \brief
	/// Sets the Client's new name
	/// \param name : new client name
	void setName(const std::string &name) noexcept;

	/// \brief
	/// Gets the Client's name
	/// \param None
	/// \return A reference to the Client's name
	const std::string &getName() const noexcept;

	/// \brief
	/// Sets this->connected to the specified value
	/// \param connected : new value of this->connected
	void setConnected(bool connected) noexcept;

	/// \brief
	/// Gets the Client's connect status
	/// \param None
	/// \return The Client's status
	bool getConnected() const noexcept;

	private:
	bool connected = true;
	bool loggedIn = false;
	std::string name;
};

#endif /* !CLIENT_HPP_ */
