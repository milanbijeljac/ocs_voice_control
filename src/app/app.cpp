#include "app.h"
#include <iostream>

void App::init()
{
	/* Input devices need to be focus, it needs to be separated */
	int number_of_devices = 0;
	m_paerror = Pa_Initialize();

	if (m_paerror != paNoError)
	{
		std::cerr << Pa_GetErrorText(m_paerror) << '\n';
		return;
	}

	number_of_devices = Pa_GetDeviceCount();

	if (number_of_devices == 0)
	{
		std::cerr << "No devices found." << '\n';
		return;
	}

	if (number_of_devices < 0)
	{
		std::cerr << Pa_GetErrorText(number_of_devices) << '\n';
		return;
	}

	/* Loop through all devices and print them in console */
	std::cout << number_of_devices << " devices found." << '\n';

	for (int i = 0; i < number_of_devices; i++)
	{
		const auto* p_pa_device_info = Pa_GetDeviceInfo(static_cast<PaDeviceIndex>(i));
		std::cout << "Device " << i  << ": " << p_pa_device_info->name << '\n';
	}
}

void App::run()
{
	if (m_paerror == paNoError)
	{
		std::cout << "Application is running." << '\n';
	}
	else
	{
		std::cerr << "Port audio is not initalized properly." << '\n';
		return;
	}
	
	while (1)
	{
		
	}
}

void App::pa_terminate()
{
	if (m_paerror == paNoError)
	{
		Pa_Terminate();
	}
	else
	{
		/* As per PA documentation */
		std::cerr << "PortAudio init returned error, cannot terminate." << '\n';
	}
}
PaError App::get_pa_status() const
{
	return m_paerror;
}
