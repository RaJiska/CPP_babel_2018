/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

#include "Client.hpp"

Client::Client()
{
}

Client::~Client()
{
}

void Client::setLoggedIn(bool loggedIn) noexcept
{
	this->loggedIn = loggedIn;
}

bool Client::getLoggedIn() const noexcept
{
	return (this->loggedIn);
}

void Client::setName(const std::string &name) noexcept
{
	this->name = name;
}

const std::string &Client::getName() const noexcept
{
	return (this->name);
}

void Client::setConnected(bool connected) noexcept
{
	this->connected = connected;
}

bool Client::getConnected() const noexcept
{
	return (this->connected);
}