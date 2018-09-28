/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessageLogin
*/

#ifndef NETWORKMESSAGELOGIN_HPP_
	#define NETWORKMESSAGELOGIN_HPP_

#include "NetworkMessage.hpp"

class NetworkMessageLogin : public NetworkMessage {
	public:
	NetworkMessageLogin();
	NetworkMessageLogin(const struct NetworkMessage::Header &header);
	~NetworkMessageLogin();

	protected:
	unsigned long long int id;
	std::string name;

	private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & id;
		ar & name;
	}
};

#endif /* !NETWORKMESSAGELOGIN_HPP_ */
