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
		std::cout << "Error: " << e.what();
	}
    
    return 0;
}

