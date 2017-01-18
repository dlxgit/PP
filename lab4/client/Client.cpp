#include "Client.h"


Client::Client(const std::string & name) :
	m_name(name)
{
	CPipe::SendMessage("Client " + name + " is connected", CPipe::READY);
	std::vector<std::string> messages;
	CPipe::WaitMessages(messages, 1, CPipe::BEGIN_CALCULATION);
	CPipe::SendMessage("Result of  " + name + " : " + std::to_string(CCalculator::CalculatePi(std::stoi(messages[0].c_str()))), CPipe::RESULT);
}