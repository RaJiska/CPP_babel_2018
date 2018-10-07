/*
** EPITECH PROJECT, 2018
** CPP_babel_2018
** File description:
** encode
*/

#include "encode.hpp"

EncoderSystem::EncoderSystem()
{
}

EncoderSystem::~EncoderSystem()
{
	if (_encode)
		opus_encoder_destroy(_encode);
	if (_decode)
		opus_decoder_destroy(_decode);
}

bool	EncoderSystem::encoderCreate()
{
	int	error;

	if ((_encode = opus_encoder_create(::SAMPLE_RATE_CODE, ::CHANNELS_CODE,
		OPUS_APPLICATION_VOIP, &error)) == NULL) {
			std::cerr << "Can not create encode" <<std::endl;
			return (false);
	}
	return (true);
}

bool	EncoderSystem::decoderCreate()
{
	int	error;

	if ((_decode = opus_decoder_create(::SAMPLE_RATE_CODE,
		::CHANNELS_CODE, &error)) == NULL) {
			std::cerr << "Can not create decoder" <<std::endl;
			return (false);
	}
	return (true);
}

unsigned char*	EncoderSystem::encode(unsigned char *data, int size)
{
	
	unsigned char	*c_bits = new unsigned char [size];

	memcpy(_in, data, size);

	_nbBytes = opus_encode(_encode, _in, ::FRAME_SIZE_CODE, c_bits, size);
	if (_nbBytes<0) {
		std::cerr << "cannot encode" << std::endl;
		return NULL;
	}
	return (c_bits);
}

unsigned char*	EncoderSystem::decode(unsigned char *data, int size)
{
	int	frame_size = opus_decode(_decode, data, size, _out,
				::MAX_FRAME_SIZE_CODE * ::CHANNELS_CODE * 2, 0);
	unsigned char	*pcm_bytes = new unsigned char
		[::MAX_FRAME_SIZE_CODE * ::CHANNELS_CODE * 2];

	if (frame_size < 0) {
		std::cerr << "cannot decode" << std::endl;
		return (NULL);
	}
	memcpy(pcm_bytes, _out, size);
	return (pcm_bytes);
}

int	EncoderSystem::getEncodeLen() const
{
	return (this->_nbBytes);
}