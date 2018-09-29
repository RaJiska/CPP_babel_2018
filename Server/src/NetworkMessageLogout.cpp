/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessageLogout
*/

#include "NetworkMessageLogout.hpp"

NetworkMessageLogout::NetworkMessageLogout() : NetworkMessage()
{
}

NetworkMessageLogout::NetworkMessageLogout(
	const struct NetworkMessage::Header &header) : NetworkMessage(header)
{
}

NetworkMessageLogout::~NetworkMessageLogout()
{
}

virtual void NetworkMessageLogout::serialize(PolyArchive ar, unsigned int) override
{

}
