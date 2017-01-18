#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <Windows.h>

namespace PipeType
{
	const std::string RESULT = "\\\\.\\pipe\\result";
	const std::string READY = "\\\\.\\pipe\\ready";
	const std::string BEGIN_CALCULATION = "\\\\.\\pipe\\begin";
}


 class CPipeWorker
{
public:
	static void WaitMessages(std::vector<std::string> & messages, size_t messageNo, std::string const & pipeName);
	static void SendMessage(std::string const & message, std::string const & pipeName);
};