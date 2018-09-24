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

	void setHeader(const NetworkMessageHeader &header);
	const NetworkMessageHeader getHeader() const;

	private:
	friend class boost::serialization::access;
	NetworkMessageHeader header;

	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & this->header;
	}
};

#endif /* !NETWORKMESSAGE_HPP_ */
