#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include "Client.h"
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")

int main()
{
    SOCKET clientSocket;
    WSADATA wsaData;
    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw SetErrorMessageText("Startup: ", WSAGetLastError());

        // type: socket stream
        if ((clientSocket = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
            throw SetErrorMessageText("Socket: ", WSAGetLastError());

        SOCKADDR_IN server;                              // параметры сокета clientSocket
        server.sin_family = AF_INET;                     // используется IP-адресация
        server.sin_port = htons(2000);                   // порт 2000
        // inet_pton?
        server.sin_addr.s_addr = inet_addr("127.0.0.1"); // любой собственный IP-адрес

        std::cout << "Connecting..." << std::endl;
        if ((connect(clientSocket, (sockaddr*)&server, sizeof(server))) == SOCKET_ERROR)
            throw SetErrorMessageText("Connect: ", WSAGetLastError());



        for (int i = 0; i < 1000; i++)
        {
            std::string numberString = std::to_string(i);
            while (numberString.length() < 3)
            numberString.insert(0, "0");
            std::string message = "Hello from client " + numberString;

            char inputBuffer[50];                       //буфер ввода
            const char* outputBuffer = message.c_str(); //буфер вывода
            int lengthInputBuffer = 0;                  //количество принятых байт
            int lengthOutputBuffer = 0;                 //количество отправленных байт

            if ((lengthOutputBuffer = send(clientSocket, outputBuffer, strlen(outputBuffer) + 1, NULL)) == SOCKET_ERROR)
                throw SetErrorMessageText("Send: ", WSAGetLastError());
            if ((lengthInputBuffer = recv(clientSocket, inputBuffer, sizeof(inputBuffer), NULL)) == SOCKET_ERROR)
                throw SetErrorMessageText("Recv: ", WSAGetLastError());

            std::cout << inputBuffer << std::endl;
        }



        if (closesocket(clientSocket) == SOCKET_ERROR)
            throw SetErrorMessageText("Close socket: ", WSAGetLastError());

        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMessageText("Cleanup: ", WSAGetLastError());
    }
    catch (std::string errorMesssageText)
    {
        std::cout << errorMesssageText;
    }
    return 0;
}
