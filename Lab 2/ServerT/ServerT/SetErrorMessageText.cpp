#include <string>
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")

std::string GetErrorMessageText(int code)
{
	std::string messageText;
	switch (code) // проверка кода возврата
	{
	case WSAEINTR: messageText = "Error code: WSAEINTR"; break;
	case WSAEACCES: messageText = "Error code: WSAEACCES"; break;
	case WSASYSCALLFAILURE: messageText = "Error code: WSASYSCALLFAILURE"; break;
	case WSAECONNREFUSED: messageText = "Connection refused! Error code: WSAECONNREFUSED"; break;
	default: messageText = "Error! Error code: " + std::to_string(code); break;
	};
	return messageText;
};

std::string SetErrorMessageText(std::string msgText, int code)
{
	return msgText + GetErrorMessageText(code);
};