/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessage
*/

#ifndef NETWORKMESSAGE_HPP_
	#define NETWORKMESSAGE_HPP_

#include "NetworkMessageHeader.hpp"

class NetworkMessage {
	public:
	NetworkMessage();
	NetworkMessage(const NetworkMessageHeader &header);
	~NetworkMessage();

	void setHeader(const NetworkMessageHeader &header);
	const NetworkMessageHeader getHeader() const;

	private:
	NetworkMessageHeader header;
};

#endif /* !NETWORKMESSAGE_HPP_ */
