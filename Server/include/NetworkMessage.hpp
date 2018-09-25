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
#include "NetworkMessageHeader.hpp"

class NetworkMessage {
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
	~NetworkMessage();

	struct NetworkMessage::Header &getHeader();

	private:
	friend class boost::serialization::access;
	struct Header header;

	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{

	}
};

#endif /* !NETWORKMESSAGE_HPP_ */
