#include "port_audio_guard.h"
#include "portaudio.h"
#include <stdexcept>
#include <tuple>
PortAudioGuard::PortAudioGuard()
{
	PaError pa_error = Pa_Initialize();

	if (pa_error != paNoError)
	{
		const char* error = Pa_GetErrorText(pa_error);
		/* As per standard throw without object to throw will just terminate object, so std::runtime_error is added */
		throw std::runtime_error(error); 
	}
}

PortAudioGuard::~PortAudioGuard()
{	
	/* Return value not used */
	std::ignore = Pa_Terminate();
}