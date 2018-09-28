/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessageClientLeft
*/

#include "NetworkMessageClientLeft.hpp"

NetworkMessageClientLeft::NetworkMessageClientLeft() : NetworkMessageLogin()
{

}

NetworkMessageClientLeft::NetworkMessageClientLeft(
	const struct NetworkMessage::Header &header) :
	NetworkMessageLogin(header)
{

}

NetworkMessageClientLeft::~NetworkMessageClientLeft()
{
}
