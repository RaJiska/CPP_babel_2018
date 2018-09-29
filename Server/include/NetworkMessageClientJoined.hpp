/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessageClientJoined
*/

#ifndef NETWORKMESSAGECLIENTJOINED_HPP_
	#define NETWORKMESSAGECLIENTJOINED_HPP_

#include "NetworkMessageLogin.hpp"

class NetworkMessageClientJoined : public NetworkMessageLogin {
	public:
	NetworkMessageClientJoined();
	NetworkMessageClientJoined(const struct NetworkMessage::Header &header);
	~NetworkMessageClientJoined();

	private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<NetworkMessageLogin>(*this);
		ar & id;
		ar & name;
	}
};

#endif /* !NETWORKMESSAGECLIENTJOINED_HPP_ */
