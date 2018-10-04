/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessage
*/

/// \file NetworkMessage.hpp
/// \brief Include file for the network messages

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
			TYPE_CALL,
			TYPE_HANGUP,
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
		bool myself;
	};

	struct MsgLogout
	{
		uint64_t id;
		bool myself;
	};

	struct MsgCall
	{
		char address[32];
	};

	/// \brief
	/// Constructor of the class NetworkMessage
	/// \param None
	NetworkMessage();

	/// \brief
	/// Constructor of the class NetworkMessage
	/// \param header : base header
	NetworkMessage(const struct NetworkMessage::Header &header);

	/// \brief
	/// Destructor of the class NetworkMessage
	/// \param None
	~NetworkMessage() = default;

	/// \brief
	/// Retrieve NetworkMessage::Header from the stored data
	/// \param None
	/// \return The extracted header as a NetworkMessage::Header *
	const struct NetworkMessage::Header *headerFromData() const noexcept;

	/// \brief
	/// Sets this->header
	/// \param header : Header to be copied
	void setHeader(struct NetworkMessage::Header &header) noexcept;

	/// \brief
	/// Gets this->header
	/// \param None
	/// \return A reference to the header structure this->header
	struct NetworkMessage::Header &getHeader();

	/// \brief
	/// Copies data of size sz to this->data
	/// \param data : to be copied
	/// \param sz : size that should be copied
	void setData(const unsigned char *data, size_t sz) noexcept;

	/// \brief
	/// Gets this->data
	/// \param None
	/// \return A pointer to the stored data
	const unsigned char *getData() const noexcept;

	private:
	struct NetworkMessage::Header header;
	unsigned char data[8192];
};

#endif /* !NETWORKMESSAGE_HPP_ */
