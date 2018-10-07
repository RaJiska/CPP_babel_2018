/*
** EPITECH PROJECT, 2018
** Client
** File description:
** IVoice
*/

#ifndef IVOICESTREAM_HPP_
	#define IVOICESTREAM_HPP_

#include <iostream>
#include <functional>
#include <boost/bind.hpp>

class IVoiceStream {
	public:
	IVoiceStream() = default;
	virtual ~IVoiceStream() = default;

	virtual void start() noexcept = 0;
	virtual void connect(
		const std::string &addr, uint16_t port) noexcept = 0;
	virtual void disconnect() noexcept = 0;
	virtual void setReadCallback(
		std::function<void(unsigned char *, size_t)>) noexcept = 0;
	virtual void writeData(
		const unsigned char *data, size_t sz) noexcept = 0;
};

#endif /* !IVOICESTREAM_HPP_ */
