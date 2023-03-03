#include <string>
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")

std::string GetErrorMessageText(int code)
{
	std::string messageText;
	switch (code) // проверка кода возврата
	{
	case WSAEINTR: messageText = "WSAEINTR"; break;
	case WSAEACCES: messageText = "WSAEACCES"; break;
		//..........коды WSAGetLastError ..........................
	case WSASYSCALLFAILURE: messageText = "WSASYSCALLFAILURE"; break;
	default: messageText = "***ERROR***"; break;
	};
	return messageText;
};

std::string SetErrorMessageText(std::string msgText, int code)
{
	return msgText + GetErrorMessageText(code);
};