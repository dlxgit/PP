#include "CPipeWorker.h"


void CPipeWorker::WaitMessages(std::vector<std::string> & messages, size_t nMessages, std::string const & pipeName)
{
	std::wstring wName(pipeName.begin(), pipeName.end());
	HANDLE hPipe = CreateNamedPipe(wName.data(),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		1024, 1024, 5000, NULL);

	if (hPipe == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("Error: invalid handle value");
	}

	for(size_t i = 0; i < nMessages; ++i)
	{
		if (ConnectNamedPipe(hPipe, NULL))
		{
			char buffer[1024];
			DWORD dwRead;
			if (ReadFile(hPipe, buffer, sizeof(buffer), &dwRead, NULL))
			{
				buffer[dwRead] = '\0';
			}
			messages.push_back(buffer);
			std::cout << buffer << std::endl;
			DisconnectNamedPipe(hPipe);
		}
	}
	CloseHandle(hPipe);
}

void CPipeWorker::SendMessage(std::string const & message, std::string const & pipeName)
{
	HANDLE hPipe;
	std::wstring wName(pipeName.begin(), pipeName.end());
	do
	{
		hPipe = CreateFile(wName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	} while (hPipe == INVALID_HANDLE_VALUE);

	const size_t LENGTH = message.length();
	DWORD dwWritten = static_cast<DWORD>(LENGTH);

	if (hPipe != INVALID_HANDLE_VALUE)
	{
		while (WriteFile(hPipe, message.data(), LENGTH, &dwWritten, NULL) == FALSE)
		{
		}
		CloseHandle(hPipe);
	}
}