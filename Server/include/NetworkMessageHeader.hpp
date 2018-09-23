/*
** EPITECH PROJECT, 2018
** Server
** File description:
**
*/

#ifndef NETWORKMESSAGEHEADER_HPP_
	#define NETWORKMESSAGEHEADER_HPP_

#include "NetworkClient.hpp"

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

	void setFrom(unsigned long long int from);
	unsigned long long int getFrom() const;
	void setTo(unsigned long long int to);
	unsigned long long int getTo() const;

	private:
	unsigned long long int from;
	unsigned long long int to;
};

#endif /* !NETWORKMESSAGEHEADER_HPP_ */
