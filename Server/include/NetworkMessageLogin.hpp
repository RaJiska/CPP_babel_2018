/*
** EPITECH PROJECT, 2018
** Server
** File description:
** NetworkMessageLogin
*/

#ifndef NETWORKMESSAGELOGIN_HPP_
	#define NETWORKMESSAGELOGIN_HPP_

#include "NetworkMessage.hpp"
#include <boost/serialization/export.hpp>

class NetworkMessageLogin : public NetworkMessage {
	public:
	NetworkMessageLogin();
	NetworkMessageLogin(const struct NetworkMessage::Header &header);
	~NetworkMessageLogin();

	void setId(unsigned long long int id) noexcept;
	unsigned long long int getId() const noexcept;
	void setName(const std::string &name) noexcept;
	const std::string &getName() const noexcept;

	virtual void serialize(PolyArchive ar, unsigned int) override;

	protected:
	unsigned long long int id;
	std::string name;
};

BOOST_CLASS_EXPORT(NetworkMessageLogin)

#endif /* !NETWORKMESSAGELOGIN_HPP_ */
