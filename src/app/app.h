#pragma once

#include "../audio/port_audio_guard.h"

class App
{
private:
	/* paGuard needs to be first to instantiate as it will triger init of PA so it will be ready for stream */
	PortAudioGuard m_paGuard;
public:
	
	void run();
	
public:
	App() = default;
	~App() = default;

	App(const App& other) = delete;
	App& operator=(const App& other) = delete;

};
