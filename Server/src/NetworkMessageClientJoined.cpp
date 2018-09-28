/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessageClientJoined
*/

#include "NetworkMessageClientJoined.hpp"

NetworkMessageClientJoined::NetworkMessageClientJoined() : NetworkMessageLogin()
{

}

NetworkMessageClientJoined::NetworkMessageClientJoined(
	const struct NetworkMessage::Header &header) :
	NetworkMessageLogin(header)
{

}

NetworkMessageClientJoined::~NetworkMessageClientJoined()
{
}
