#include <iostream>
#include "Server.h"

int main()
{
	constexpr int DEFAULT_PORT = 69;

	Server* serverHandler = new Server(DEFAULT_PORT);
	printf("Server successfuly setup and listening on port %d\n", DEFAULT_PORT);


	while (1)
	{
		unsigned clientId = serverHandler->acceptNewClients();
		if (clientId)
		{
			//TODO: - access newly connected user [DONE] 
			//		- send currently connected users
			const Client* client = serverHandler->GetClientInfo(clientId);
			printf("New Connection from %s client ID %d\n", client->GetClientIpAddr(), clientId);
			std::string welcomeMsg = "Welcome OwO\n";
			send(client->GetSocket(), welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
		}

		//Process existing users
		for (auto it = serverHandler->sessions.cbegin(); it != serverHandler->sessions.cend();)
		{
			bool disconnecting = false;

			//iterate through all users
			printf("Checking userId %d:\n", (*it)->GetClientId());
			printf("test 1\n");
			char buff[4096];
			ZeroMemory(buff, 4096);
			//recv stream from user
			int msg_len = recv((*it)->GetSocket(), buff, 4096, 0);
			printf("test 2\n");

			if (msg_len <= 0)
			{
				printf("test 3\n");
				disconnecting = true;
				closesocket((*it)->GetSocket());
				printf("Client closed connection\n");
			}
			else
			{
				printf("test 4\n");
				printf("recv from user %d: %s\n", (*it)->GetClientId(), std::string(buff, msg_len).c_str());
			}
			
			printf("test 5\n");
			//if (buff[0])
			//send((*it)->GetSocket(), buff, msg_len + 1, 0);

			//check if command or message

			//send stream to other users

			if (disconnecting)
			{
				printf("test 6\n");
				serverHandler->sessions.erase(it++);
			}
			else
			{
				printf("test 7\n");
				++it;
			}
		}
	}

	WSACleanup();


	//While loop for accepting and echoing messages back to client
	/*
	FOR SINGLE CLIENT ONLY

	//Wait for connection from a client
	sockaddr_in client_addr;
	int client_addr_len = sizeof(client_addr);

	SOCKET clientSocket = accept(listeningSocket, (sockaddr*)&client_addr, &client_addr_len);


	//Print Client info
	char host[NI_MAXHOST];			//client remote name
	char clientPort[NI_MAXSERV];	//port of client

	ZeroMemory(host, NI_MAXHOST);		//similar to memset but for windows
	ZeroMemory(clientPort, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client_addr, sizeof(client_addr), host, NI_MAXHOST, clientPort, NI_MAXSERV, 0) == 0)
	{
		printf("%s conencted on port %s\n", host, clientPort);
	}
	else
	{
		inet_ntop(AF_INET, &client_addr.sin_addr, host, NI_MAXHOST);
		printf("%s connected on port %d\n", host, ntohs(client_addr.sin_port));
	}

	char buff[4096];
	while (true)
	{
		ZeroMemory(buff, 4096);

		int msg_len = recv(clientSocket, buff, sizeof(buff), 0);
		if (msg_len == SOCKET_ERROR)
		{
			printf("recv Failed: %d\n", WSAGetLastError());
			WSACleanup();
			return -1;
		}

		if (!msg_len)
		{
			printf("Client closed connection\n");
			break;
		}

		send(clientSocket, buff, msg_len + 1, 0);
	}

	closesocket(clientSocket);
	
	*/
	return 0;
}