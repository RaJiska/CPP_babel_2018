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
			Voice();
			~Voice();
  			bool	initPa();
  			bool	openStream();
  			bool	startStream();
  			bool	initStream();                                   
  			bool	initParams() const;
			bool	initInputParams();
			bool	initOutputParams();
			bool	initParams();
			bool	writeOnStream(unsigned char *buff);
			bool	readFromStream(unsigned char *buff);
			void	cleanReadBuffer();
			int	getReadBufferSize() const;
			unsigned char	*getReadBuffer() const;

};

#endif /* !VOICE_HPP_ */
