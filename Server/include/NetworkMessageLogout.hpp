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

	virtual void serialize(PolyArchive ar, unsigned int) override;

	private:
	unsigned long long int id;
};

#endif /* !NETWORKMESSAGELOGOUT_HPP_ */
