/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessageClientLeft
*/

#ifndef NETWORKMESSAGECLIENTLEFT_HPP_
	#define NETWORKMESSAGECLIENTLEFT_HPP_

#include "NetworkMessageLogin.hpp"

class NetworkMessageClientLeft : public NetworkMessageLogin {
	public:
	NetworkMessageClientLeft();
	NetworkMessageClientLeft(const struct NetworkMessage::Header &header);
	~NetworkMessageClientLeft();

	private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & id;
		ar & name;
	}
};

#endif /* !NETWORKMESSAGECLIENTLEFT_HPP_ */
