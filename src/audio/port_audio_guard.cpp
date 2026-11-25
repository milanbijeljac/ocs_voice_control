#include "port_audio_guard.h"
#include "portaudio.h"
#include <stdexcept>

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
	/* Return value not used: a destructor has nowhere to report it, and this
	class must not decide how errors are displayed. */
	Pa_Terminate();
}
