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

void NetworkMessageLogin::serialize(PolyArchive ar, unsigned int)
{
	boost::apply_visitor(visitor::make_visitor([=](auto& ar) {
		//ar & boost::serialization::base_object<NetworkMessage>(*this);
		ar & this->id;
		ar & this->name;
	}), ar);
}

void NetworkMessageLogin::setId(unsigned long long int id) noexcept
{
	this->id = id;
}

unsigned long long int NetworkMessageLogin::getId() const noexcept
{
	return (this->id);
}

void NetworkMessageLogin::setName(const std::string &name) noexcept
{
	this->name = name;
}

const std::string &NetworkMessageLogin::getName() const noexcept
{
	return (this->name);
}