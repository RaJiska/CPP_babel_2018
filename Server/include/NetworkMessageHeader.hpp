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
		TYPE_LOGOUT,
		TYPE_CONTROL,
		TYPE_VOICE
	};

	NetworkMessageHeader();
	NetworkMessageHeader(unsigned long long int to);
	~NetworkMessageHeader();

	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & this->type;
		ar & this->to;
		ar & this->from;
	}

	void setFrom(unsigned long long int from);
	unsigned long long int getFrom() const;
	void setTo(unsigned long long int to);
	unsigned long long int getTo() const;

	private:
	enum MessageType type;
	unsigned long long int from;
	unsigned long long int to;
};

#endif /* !NETWORKMESSAGEHEADER_HPP_ */
