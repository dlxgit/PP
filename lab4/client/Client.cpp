#include "Client.h"


Client::Client(const std::string & name) :
	m_name(name)
{
	CPipeWorker::SendMessage("Client " + name + " is connected", PipeType::READY);
	std::vector<std::string> messages;
	CPipeWorker::WaitMessages(messages, 1, PipeType::BEGIN_CALCULATION);
	CPipeWorker::SendMessage("Result of  " + name + " : " + std::to_string(CCalculator::CalculatePi(std::stoi(messages[0].c_str()))), PipeType::RESULT);
}