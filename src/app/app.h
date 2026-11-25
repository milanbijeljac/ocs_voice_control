#pragma once

#include "audio/port_audio_guard.h"

class App
{
private:
	/* m_pa_guard needs to be first to instantiate as it will trigger init of PA so it will be ready for stream 
	PA needs to be destroyed last, or after the stream ends */
	PortAudioGuard m_pa_guard;
public:
	
	void run();
	
public:
	App() = default;
	~App() = default;

	App(const App& other) = delete;
	App& operator=(const App& other) = delete;

};
