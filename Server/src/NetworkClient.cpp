/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Client
*/

#include "NetworkClient.hpp"

NetworkClient::NetworkClient(unsigned long long int id,
	boost::asio::io_service &service) : id(id), socket(service)
{
}

NetworkClient::~NetworkClient()
{
}

boost::asio::ip::tcp::socket &NetworkClient::getSocket() noexcept
{
	return this->socket;
}
