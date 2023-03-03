#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Server.h"
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")

int main()
{
    SOCKET serverSocket;
    WSADATA wsaData;
    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw SetErrorMessageText("Startup:", WSAGetLastError());

        for (;;)
        {
            // type: socket stream
            if ((serverSocket = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
                throw SetErrorMessageText("Socket:", WSAGetLastError());

            SOCKADDR_IN server;                  // параметры сокета serverSocket
            server.sin_family = AF_INET;         // используется IP-адресация
            server.sin_port = htons(2000);       // порт 2000
            server.sin_addr.s_addr = INADDR_ANY; // любой собственный IP-адрес

            std::cout << "Awaiting connection..." << std::endl;
            if (bind(serverSocket, (LPSOCKADDR)&server, sizeof(server)) == SOCKET_ERROR)
                throw SetErrorMessageText("Bind:", WSAGetLastError());

            if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
                throw SetErrorMessageText("Listen:", WSAGetLastError());

            SOCKET clientSocket;                // сокет для обмена данными с клиентом
            SOCKADDR_IN client;                 // параметры сокета клиента
            memset(&client, 0, sizeof(client)); // обнулить память
            int lengthClient = sizeof(client);  // размер SOCKADDR_IN

            if ((clientSocket = accept(serverSocket, (sockaddr*)&client, &lengthClient)) == INVALID_SOCKET)
                throw SetErrorMessageText("Accept:", WSAGetLastError());

            std::cout << "Client connected: " << inet_ntoa(client.sin_addr);
            std::cout << ":" << htons(client.sin_port) << std::endl;



            for (;;)
            {
                char inputBuffer[50];      //буфер ввода
                int lengthInputBuffer = 0; //количество принятых байт

                if ((lengthInputBuffer = recv(clientSocket, inputBuffer, sizeof(inputBuffer), NULL)) == SOCKET_ERROR)
                    throw SetErrorMessageText("Recv: ", WSAGetLastError());
                std::cout << inputBuffer << std::endl;
                if ((lengthInputBuffer = send(clientSocket, inputBuffer, sizeof(inputBuffer), NULL)) == SOCKET_ERROR)
                    throw SetErrorMessageText("Send: ", WSAGetLastError());

                if (inputBuffer[18] == '9' && inputBuffer[19] == '9' && inputBuffer[20] == '9')
                    break;
            }



            if (closesocket(serverSocket) == SOCKET_ERROR)
                throw SetErrorMessageText("Close socket:", WSAGetLastError());
        }

        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMessageText("Cleanup:", WSAGetLastError());
    }
    catch (std::string errorMesssageText)
    {
        std::cout << errorMesssageText;
    }
    return 0;
}
