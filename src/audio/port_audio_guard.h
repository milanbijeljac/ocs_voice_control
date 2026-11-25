#pragma once

class PortAudioGuard
{
public:
	PortAudioGuard();

	~PortAudioGuard();

	/* Prevent copying of PortAudioGuard object as there can exist only one.
	Moving is deleted as well: a moved-from guard would have to remember not to
	terminate PortAudio, which is the flag this class exists to get rid of. */
	PortAudioGuard(const PortAudioGuard&) = delete;
	PortAudioGuard& operator=(const PortAudioGuard&) = delete;
	PortAudioGuard(PortAudioGuard&&) = delete;
	PortAudioGuard& operator=(PortAudioGuard&&) = delete;
};
