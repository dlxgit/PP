#include "CPipeWorker.h"
#include "Client.h"
#include <random>
#include <string>
#include<math.h> 
#include <ctime>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Error: incorrect input. Usage: client.exe <name>" << std::endl;
		return 1;
	}

	try
	{
		Client client(argv[1]);
		
	}
	catch (const std::invalid_argument & ex)
	{
		std::cout << ex.what() << std::endl;
		return 2;
	}
	catch (const std::runtime_error & ex)
	{
		std::cout << ex.what() << std::endl;
		return 3;
	}

	return 0;
}