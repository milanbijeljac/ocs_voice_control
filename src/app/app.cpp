#include "app.h"

void App::init()
{
	App::m_paerror = Pa_Initialize();
}

void App::run()
{
	std::cout << "Application is running." << std::endl;
	while (1)
	{
		
	}
}

void App::pa_terminate()
{
	if (App::m_paerror == paNoError)
	{
		Pa_Terminate();
	}
	else
	{
		std::cout << "PortAudio init returned error, cannot terminate.";
	}
}
PaError App::get_pa_status()
{
	return m_paerror;
}
