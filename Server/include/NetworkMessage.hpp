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
	NetworkMessage();
	NetworkMessage(const NetworkMessageHeader &header);
	~NetworkMessage();


	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & this->header;
	}

	void setHeader(const NetworkMessageHeader &header);
	const NetworkMessageHeader getHeader() const;

	private:
	NetworkMessageHeader header;
};

#endif /* !NETWORKMESSAGE_HPP_ */
