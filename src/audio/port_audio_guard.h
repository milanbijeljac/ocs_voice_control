#pragma once



class PortAudioGuard
{
public:
	PortAudioGuard();

	~PortAudioGuard();

	/* Prevent copying of PortAudioGuard object as there can exist only one */
	PortAudioGuard(const PortAudioGuard& temp_obj) = delete;
	PortAudioGuard& operator=(const PortAudioGuard& temp_obj) = delete;
};
