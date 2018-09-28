/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessageLogout
*/

#ifndef NETWORKMESSAGELOGOUT_HPP_
	#define NETWORKMESSAGELOGOUT_HPP_

#include "NetworkMessage.hpp"

class NetworkMessageLogout : public NetworkMessage {
	public:
	NetworkMessageLogout();
	NetworkMessageLogout(const struct NetworkMessage::Header &header);
	~NetworkMessageLogout();

	private:
	friend class boost::serialization::access;
	unsigned long long int id;

	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & id;
	}
};

#endif /* !NETWORKMESSAGELOGOUT_HPP_ */
