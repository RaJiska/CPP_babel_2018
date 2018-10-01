/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessage
*/

#include <cstring>
#include "NetworkMessage.hpp"

NetworkMessage::NetworkMessage()
{
}

NetworkMessage::NetworkMessage(const struct NetworkMessage::Header &header) :
	header(header)
{
}

const struct NetworkMessage::Header *NetworkMessage::headerFromData()
	const noexcept
{
	static struct NetworkMessage::Header *header =
		(struct NetworkMessage::Header *) &this->data[0];
	return (header);
}

void NetworkMessage::setData(const unsigned char *data, size_t sz) noexcept
{
	std::memcpy(&this->data[0], data, sz);
}

const unsigned char *NetworkMessage::getData() const noexcept
{
	return (&this->data[0]);
}

void NetworkMessage::setHeader(struct NetworkMessage::Header &header) noexcept
{
	this->header = header;
}

struct NetworkMessage::Header &NetworkMessage::getHeader()
{
	return(this->header);
}