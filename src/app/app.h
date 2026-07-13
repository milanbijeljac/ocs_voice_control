#pragma once

#include <iostream>
#include "portaudio.h"

class App
{

private:
	PaError m_paerror;

public:
	void init();
	void run();
	void pa_terminate();
public:
	App() : m_paerror(paNotInitialized)
	{
		init();
	};
	~App() 
	{
		pa_terminate();
	};

	

	PaError get_pa_status();
};
