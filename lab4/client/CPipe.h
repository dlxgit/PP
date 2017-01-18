#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <Windows.h>


 class CPipe
{
public:
	const static std::string RESULT;
	const static std::string READY;
	const static std::string BEGIN_CALCULATION;

	static void WaitMessages(std::vector<std::string> & messages, size_t messageNo, std::string const & pipeName);
	static void SendMessage(std::string const & message, std::string const & pipeName);
};