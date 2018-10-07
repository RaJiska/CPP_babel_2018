/*
** EPITECH PROJECT, 2018
** cpp_babel
** File description:
** voip project
*/

#ifndef VOICE_HPP_
	#define VOICE_HPP_


	#include <portaudio.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <iostream>
	#include <unistd.h>

	const int NUM_CHANNELS = 2;
	const double SAMPLE_RATE = 4000;
	const int FRAMES_PER_BUFFER = 1024;
	const int SAMPLE_SIZE = 3;
	const int FRAME_SIZE = 960;
	const PaSampleFormat PA_SAMPLE_TYPE = paInt16;

	class Voice {
 		private:
			PaStream	*_stream;
			int	_readBufferSize;
			PaStreamParameters	_inputParam;
			PaStreamParameters	_outputParam;
			unsigned char	*_readBuffer;

		public:

			/// \brief
			/// Constructor of the class Voice
			/// \param None
			Voice();

			/// \brief
			/// Destructor of the class Voice
			/// \param None
			~Voice();

			/// \brief
			/// Initialises PortAudio
			/// \param None
			/// \return True uppon success, Fail otherwise
  			bool	initPa();

			/// \brief
			/// Opens the audio stream
			/// \param None
			/// \return True uppon success, Fail otherwise
  			bool	openStream();

			/// \brief
			/// Starts the audio stream
			/// \param None
			/// \return True uppon success, Fail otherwise
  			bool	startStream();

			/// \brief
			/// Opens and starts the audio stream
			/// \param None
			/// \return True uppon success, Fail otherwise
  			bool	initStream();

			/// \brief
			/// Initialise the input and output devices
			/// \param None
			/// \return True uppon success, Fail otherwise
  			bool	initParams() const;

			/// \brief
			/// Initialise the input devices
			/// \param None
			/// \return True uppon success, Fail otherwise
			bool	initInputParams();

			/// \brief
			/// Initialise the output devices
			/// \param None
			/// \return True uppon success, Fail otherwise
			bool	initOutputParams();

			/// \brief
			/// Initialise the input and output devices
			/// \param None
			/// \return True uppon success, Fail otherwise
			bool	initParams();

			/// \brief
			/// Writes on the audio stream
			/// \param data : Buffer to write on
			/// \return True uppon success, Fail otherwise
			bool	writeOnStream(unsigned char *buff);

			/// \brief
			/// Reads from the audio stream
			/// \param None
			/// \return True uppon success, Fail otherwise
			bool	readFromStream();

			/// \brief
			/// Cleans the read buffer
			/// \param None
			void	cleanReadBuffer();

			/// \brief
			/// Returns the length of the read buffer
			/// \param None
			/// \return The length of the read buffer
			int	getReadBufferSize() const;

			/// \brief
			/// Gets this->_readBuffer
			/// \param None
			/// \return The read buffer
			unsigned char	*getReadBuffer() const;
};

#endif /* !VOICE_HPP_ */
