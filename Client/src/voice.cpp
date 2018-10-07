/*
** EPITECH PROJECT, 2018
** cpp_babel
** File description:
** voice
*/

#include "voice.hpp"

Voice::Voice()
{
	_stream = NULL;
	_readBufferSize = ::FRAMES_PER_BUFFER * ::NUM_CHANNELS * ::SAMPLE_SIZE;
	_readBuffer= new unsigned char [_readBufferSize];
}

Voice::~Voice()
{
}

bool	Voice::initPa()
{
	if ((Pa_Initialize()) != paNoError)
		return (false);
	return (true);
}

bool	Voice::openStream()
{
	if ((Pa_OpenStream(&_stream, &_inputParam, &_outputParam, ::SAMPLE_RATE,
		::FRAMES_PER_BUFFER, paClipOff, NULL, NULL)) != paNoError)
		return (false);
	return (true);
}

bool	Voice::startStream()
{
	if ((Pa_StartStream(_stream)) != paNoError)
		return (false);
	return (true);
}

bool	Voice::initStream()
{
	if ((openStream()) == false)
		std::cerr << "can not open stream" << std::endl;
	if ((startStream()) == false)
		std::cerr << "cannot start stream" <<std::endl;
	return (true);
}

bool	Voice::initParams()
{
	if ((initPa()) == false)
		std::cerr << "can not ijnit PA" << std::endl;
	initInputParams();
	initOutputParams();
	return (true);
}

bool	Voice::initInputParams()
{
	if ((_inputParam.device = Pa_GetDefaultInputDevice()) == paNoDevice)
		return (false);
	_inputParam.channelCount = 2;
	_inputParam.sampleFormat = ::PA_SAMPLE_TYPE;
	_inputParam.suggestedLatency = Pa_GetDeviceInfo(_inputParam.device)->defaultLowInputLatency;
	_inputParam.hostApiSpecificStreamInfo = NULL;
	return (true);
}

bool	Voice::initOutputParams()
{
	if ((_outputParam.device = Pa_GetDefaultInputDevice()) == paNoDevice)
		return (false);
	_outputParam.channelCount = 2;
	_outputParam.sampleFormat = ::PA_SAMPLE_TYPE;
	_outputParam.suggestedLatency = Pa_GetDeviceInfo(_outputParam.device)->defaultLowInputLatency;
	_outputParam.hostApiSpecificStreamInfo = NULL;
	return (true);
}

bool	Voice::writeOnStream(unsigned char *buff)
{
	if ((Pa_WriteStream(_stream, buff, ::FRAMES_PER_BUFFER)) != paNoError) {
		std::cout << "FAIL WRITE" <<std::endl;
		return (false);
	}
	return (true);
}

bool	Voice::readFromStream(unsigned char *buff)
{
	if ((Pa_ReadStream(_stream, buff, ::FRAMES_PER_BUFFER)) != paNoError)
		return (false);
	return (true);
}

void	Voice::cleanReadBuffer()
{
	for (int i = 0; i != _readBufferSize; i++)
		_readBuffer[i] = 0;
}

int	Voice::getReadBufferSize() const
{
	return (_readBufferSize);
}

unsigned char	*Voice::getReadBuffer() const
{
	return (_readBuffer);
}