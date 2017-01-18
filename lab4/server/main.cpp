#include "../client/CPipeWorker.h"
#include "CServer.h"

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "Error: incorrect input. Usage: server.exe <nIterations> <nClients>";
		return 1;
	}

	try
	{
		CServer(std::stoi(argv[1]), std::stoi(argv[2]));
	}
	catch(const std::invalid_argument & ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch(const std::runtime_error & ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}