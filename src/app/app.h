#pragma once

#include "portaudio.h"

class App
{

private:
	PaError m_paerror;
private:
	void pa_terminate();
	void init();
public:
	
	void run();
	
public:
	App() : m_paerror(paNotInitialized)
	{
		init();
	};
	~App() 
	{
		pa_terminate();
	};

	App(const App& other) = delete;
	App& operator=(const App& other) = delete;

	PaError get_pa_status() const;

};
