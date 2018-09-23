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

NetworkMessage::~NetworkMessage()
{
}

void NetworkMessage::setHeader(const NetworkMessageHeader &header)
{
	this->header = header;
}

const NetworkMessageHeader NetworkMessage::getHeader() const
{
	return (this->header);
}