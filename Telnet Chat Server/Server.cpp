#include <iostream>
#include "Server.h"

Server::Server(int const defaultPort)
{
	//Socket initialization
	WSADATA wsaData;
	listeningSocket = INVALID_SOCKET;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR)
	{
		printf("WSAStartup Failed: %d\n", WSAGetLastError());
		WSACleanup();
		exit(1);
	}

	//binding of ip adreses and port to socket
	sockaddr_in hints;
	hints.sin_family = AF_INET;
	hints.sin_port = htons(defaultPort); //port here
	hints.sin_addr.s_addr = INADDR_ANY;

	//socket Creation
	listeningSocket = socket(AF_INET, SOCK_STREAM, 0); //SOCK_STREAM is for TCP
	if (listeningSocket == INVALID_SOCKET)
	{
		printf("socket Failed: %d\n", WSAGetLastError());
		WSACleanup();
		exit(1);
	}

	if (bind(listeningSocket, (sockaddr*)&hints, sizeof(hints)) == SOCKET_ERROR)
	{
		printf("bind Failed: %d\n", WSAGetLastError());
		WSACleanup();
		exit(1);
	}

	if (listen(listeningSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("listen Failed: %d\n", WSAGetLastError());
		WSACleanup();
		exit(1);
	}
}

Server::~Server()
{
}

void Server::AcceptNewClients()
{
	while (1)
	{
		sockaddr_in clientInfo;
		int clientInfoLen = sizeof(clientInfo);

		SOCKET clientSocket = accept(listeningSocket, (sockaddr*)&clientInfo, &clientInfoLen);

		if (clientSocket != INVALID_SOCKET)
		{
			Client* client = new Client(clientCounter, clientSocket, clientInfo);
			sessions.push_back(client);

			//TODO: - access newly connected user [DONE] 
			//		- send currently connected users
			printf("New Connection from %s client ID %d\n", client->GetClientIpAddr(), clientCounter);
			std::string welcomeMsg = "Welcome\n";
			send(clientSocket, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
		}
	}
}

const Client* Server::GetClientInfo(unsigned clientId)
{
	for (auto it = sessions.begin(); it != sessions.end(); it++)
	{
		if ((*it)->GetClientId() == clientId)
		{
			return *it;
		}
	}
	return nullptr;
}
