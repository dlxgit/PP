#include "../client/CPipe.h"

void WaitForClients(size_t nIterations, size_t nClients)
{
	std::vector<std::string> messageList;
	CPipe::WaitMessages(std::vector<std::string>(), nClients, CPipe::READY);
	std::cout << "Clients are connected" << std::endl;
	std::string message(std::to_string(nIterations / nClients));
	for (auto i = 0; i < nClients; ++i)
	{
		CPipe::SendMessage(message, CPipe::BEGIN_CALCULATION);
	}

	CPipe::WaitMessages(std::ref(messageList), nClients, CPipe::RESULT);
}


int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "Error: incorrect input. Usage: server.exe <nIterations> <nClients>";
		return 1;
	}

	try
	{
		size_t nIterations = std::stoi(argv[1]);
		WaitForClients(nIterations, std::stoi(argv[2]));
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