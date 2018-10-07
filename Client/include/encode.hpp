/*
** EPITECH PROJECT, 2018
** CPP_babel_2018
** File description:
** encode
*/

#ifndef ENCODE_HPP_
	#define ENCODE_HPP_

	#include <opus_types.h>
	#include <opus.h>
	#include <cstring>
	#include <iostream>

	const int FRAME_SIZE_CODE = 960;
	const int SAMPLE_RATE_CODE = 8000;
	const int CHANNELS_CODE = 2;
	const int MAX_FRAME_SIZE_CODE = 2*960;

	class	EncoderSystem {
		private:
			OpusEncoder	*_encode;
			OpusDecoder	*_decode;
			opus_int16	_in[FRAME_SIZE_CODE*CHANNELS_CODE];
			opus_int16	_out[MAX_FRAME_SIZE_CODE*CHANNELS_CODE];
			int	_nbBytes;

		public:
			EncoderSystem();
			~EncoderSystem();

			/// \brief
			/// Creates the encoder for later use
			/// \param None
			bool	encoderCreate();

			/// \brief
			/// Creates the decoder for later use
			/// \param None
			bool	decoderCreate();

			/// \brief
			/// Encodes the data of specified size
			/// \param data : Buffer to compress
			/// \param size : Buffer's size
			/// \return The encoded data
			unsigned char*	encode(unsigned char *, int);

			/// \brief
			/// Decodes the data of specified size
			/// \param data : Buffer to compress
			/// \param size : Buffer's size
			/// \return The decoded data
			unsigned char*	decode(unsigned char *, int);

			/// \brief
			/// Gets this->_nbBytes
			/// \param None
			/// \return The encoded length
			int	getEncodeLen() const;
};

#endif /* !ENCODE_HPP_ */
