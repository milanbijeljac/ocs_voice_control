#include "port_audio_guard.h"
#include "portaudio.h"
#include <stdexcept>

PortAudioGuard::PortAudioGuard()
{
	/* Input devices need to be focus, it needs to be separated */
	PaError m_paerror = Pa_Initialize();

	if (m_paerror != paNoError)
	{
		const char* error = Pa_GetErrorText(m_paerror);
		std::runtime_error rt_error(error);
		throw rt_error;		/* As per standard throw without object to throw will just terminate object, so std::runtime_error is added */
	}
}

PortAudioGuard::~PortAudioGuard()
{
	Pa_Terminate();
}