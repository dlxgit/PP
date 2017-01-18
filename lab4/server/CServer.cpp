#include "CServer.h"

CServer::CServer(size_t nIterations, size_t nClients)
{
	std::vector<std::string> messageList;
	CPipeWorker::WaitMessages(std::vector<std::string>(), nClients, PipeType::READY);
	std::cout << "Clients are connected" << std::endl;
	std::string message(std::to_string(nIterations / nClients));
	for (auto i = 0; i < nClients; ++i)
	{
		CPipeWorker::SendMessage(message, PipeType::BEGIN_CALCULATION);
	}

	CPipeWorker::WaitMessages(std::ref(messageList), nClients, PipeType::RESULT);
}