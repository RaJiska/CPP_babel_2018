/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessageHeader
*/

#include "NetworkMessageHeader.hpp"

NetworkMessageHeader::NetworkMessageHeader()
{
}

NetworkMessageHeader::NetworkMessageHeader(unsigned long long int to) : to(to)
{
}

NetworkMessageHeader::~NetworkMessageHeader()
{
}

void NetworkMessageHeader::setFrom(unsigned long long int from) noexcept
{
	this->from = from;
}

unsigned long long int NetworkMessageHeader::getFrom() const noexcept
{
	return (this->from);
}

void NetworkMessageHeader::setTo(unsigned long long int to) noexcept
{
	this->to = to;
}

unsigned long long int NetworkMessageHeader::getTo() const noexcept
{
	return (this->to);
}

void NetworkMessageHeader::setType(
	NetworkMessageHeader::MessageType type) noexcept
{
	this->type = type;
}

NetworkMessageHeader::MessageType NetworkMessageHeader::getType() const noexcept
{
	return (this->type);
}