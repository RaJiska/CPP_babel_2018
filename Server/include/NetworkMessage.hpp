/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessage
*/

#ifndef NETWORKMESSAGE_HPP_
	#define NETWORKMESSAGE_HPP_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "INetworkMessage.hpp"
#include "NetworkMessageHeader.hpp"

class NetworkMessage : public INetworkMessage {
	public:
	struct Header
	{
		enum MessageType
		{
			TYPE_LOGIN,
			TYPE_LOGOUT,
			TYPE_CONTROL,
			TYPE_VOICE
		};
		unsigned long long int to;
		unsigned long long int from;
		enum MessageType type;
		size_t size;
	};

	NetworkMessage();
	NetworkMessage(const struct NetworkMessage::Header &header);
	virtual ~NetworkMessage() = 0;

	struct NetworkMessage::Header &getHeader();
	virtual void serialize(PolyArchive ar, unsigned int) = 0;

	private:
	struct Header header;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(NetworkMessage)

#endif /* !NETWORKMESSAGE_HPP_ */
