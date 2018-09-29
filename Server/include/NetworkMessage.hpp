/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessage
*/

#ifndef NETWORKMESSAGE_HPP_
	#define NETWORKMESSAGE_HPP_

#include <cstdint>

class NetworkMessage {
	public:
	struct Header
	{
		enum MessageType
		{
			TYPE_ERROR,
			TYPE_LOGIN,
			TYPE_LOGOUT,
			TYPE_VOICE
		};
		uint64_t to;
		uint64_t from;
		uint8_t type;
		uint64_t size;
	};

	struct MsgLogin
	{
		uint64_t id;
		char name[32];
	};

	struct MsgLogout
	{
		uint64_t id;
	};
	NetworkMessage();
	NetworkMessage(const struct NetworkMessage::Header &header);
	~NetworkMessage() = default;

	const struct NetworkMessage::Header *headerFromData() const noexcept;
	struct NetworkMessage::Header &getHeader();

	void setData(const unsigned char *data, size_t sz) noexcept;
	const unsigned char *getData() const noexcept;

	private:
	struct NetworkMessage::Header header;
	unsigned char data[8192];
};

#endif /* !NETWORKMESSAGE_HPP_ */
