/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessageLogin
*/

#include "NetworkMessageLogin.hpp"

NetworkMessageLogin::NetworkMessageLogin() : NetworkMessage()
{
}

NetworkMessageLogin::NetworkMessageLogin(
	const struct NetworkMessage::Header &header) : NetworkMessage(header)
{
}

NetworkMessageLogin::~NetworkMessageLogin()
{
}
