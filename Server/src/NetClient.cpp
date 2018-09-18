/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

#include "NetClient.hpp"

NetClient::NetClient(unsigned long long int id,
	boost::asio::io_service &service) : id(id), socket(service)
{
}

NetClient::~NetClient()
{
}

boost::asio::ip::tcp::socket &NetClient::getSocket() noexcept
{
	return this->socket;
}
