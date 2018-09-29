/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessage
*/

#include "NetworkMessage.hpp"

NetworkMessage::NetworkMessage()
{
}

NetworkMessage::NetworkMessage(const struct NetworkMessage::Header &header) :
	header(header)
{
}

NetworkMessage::~NetworkMessage()
{
}

struct NetworkMessage::Header &NetworkMessage::getHeader()
{
	return (this->header);
}