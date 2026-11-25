#include <iostream>
#include <exception>
#include "app/app.h"

int main()
{
    
	try
	{
		App app;
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
    
    return 0;
}

