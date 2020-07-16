#include <iostream>
#include <thread>
#include "Server.h"

void AcceptNewClients(Server* serverHandler)
{
	serverHandler->AcceptNewClients();
}

void ProcessUsers(Server* serverHandler)
{
	while (1)
	{
		for (auto it = serverHandler->sessions.cbegin(); it != serverHandler->sessions.cend(); ++it)
		{
			bool disconnecting = false;

			char buff[256];
			ZeroMemory(buff, 256);
			//recv stream from user
			int msg_len = recv((*it)->GetSocket(), buff, 4096, 0);

			if (msg_len <= 0)
			{
				disconnecting = true;
				closesocket((*it)->GetSocket());
				printf("Client closed connection\n");
			}
			else
			{
				printf("recv from user %d: %s\n", (*it)->GetClientId(), std::string(buff, msg_len).c_str());
			}
			
			//check if command or message
			//if (buff[0] == "\\")
			//{

			//}
			//else
			//{
					//send stream to other users
			//}
			//send((*it)->GetSocket(), buff, msg_len + 1, 0);

			if (disconnecting)
			{
				serverHandler->sessions.erase(it++);
			}
		}
	}
}

int main()
{
	constexpr int DEFAULT_PORT = 69;

	Server* serverHandler = new Server(DEFAULT_PORT);
	printf("Server successfuly setup and listening on port %d\n", DEFAULT_PORT);

	std::thread connectionHandler(AcceptNewClients, serverHandler);
	std::thread messageHandler(ProcessUsers, serverHandler);
	connectionHandler.join();
	messageHandler.join();

	WSACleanup();


	return 0;
}



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
