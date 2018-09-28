/*
** EPITECH PROJECT, 2018
** Server
** File description:
**
*/

#ifndef NETWORKMESSAGEHEADER_HPP_
	#define NETWORKMESSAGEHEADER_HPP_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class NetworkMessageHeader {
	public:
	enum MessageType
	{
		TYPE_LOGIN,
		TYPE_CLIENT_JOINED,
		TYPE_LOGOUT,
		TYPE_CLIENT_LEFT,
		TYPE_CONTROL,
		TYPE_VOICE
	};

	NetworkMessageHeader();
	NetworkMessageHeader(unsigned long long int to);
	~NetworkMessageHeader();

	void setFrom(unsigned long long int from) noexcept;
	unsigned long long int getFrom() const noexcept;
	void setTo(unsigned long long int to) noexcept;
	unsigned long long int getTo() const noexcept;
	void setType(NetworkMessageHeader::MessageType type) noexcept;
	NetworkMessageHeader::MessageType getType() const noexcept;

	private:
	friend class boost::serialization::access;
	enum MessageType type;
	unsigned long long int from;
	unsigned long long int to;

	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & this->type;
		ar & this->to;
		ar & this->from;
	}
};

#endif /* !NETWORKMESSAGEHEADER_HPP_ */
