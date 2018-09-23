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

void NetworkMessageHeader::setFrom(unsigned long long int from)
{
	this->from = from;
}

unsigned long long int NetworkMessageHeader::getFrom() const
{
	return (this->from);
}

void NetworkMessageHeader::setTo(unsigned long long int to)
{
	this->to = to;
}

unsigned long long int NetworkMessageHeader::getTo() const
{
	return (this->to);
}
