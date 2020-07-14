#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_PORT 27

int main()
{
	//Socket initialization
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR)
	{
		printf("WSAStartup Failed: %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	//binding of ip adreses and port to socket
	sockaddr_in hints;
	hints.sin_family		= AF_INET;
	hints.sin_port			= htons(DEFAULT_PORT); //port here
	hints.sin_addr.s_addr	= INADDR_ANY;

	//socket Creation
	SOCKET listeningSocket;
	listeningSocket = socket(AF_INET, SOCK_STREAM, 0); //SOCK_STREAM is for TCP

	if (listeningSocket == INVALID_SOCKET)
	{
		printf("socket Failed: %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	if (bind(listeningSocket, (sockaddr*)&hints, sizeof(hints)) == SOCKET_ERROR)
	{
		printf("bind Failed: %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	if (listen(listeningSocket, 5) == SOCKET_ERROR)
	{
		printf("listen Failed: %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	
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

	//While loop for accepting and echoing messages back to client
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
	WSACleanup();
	return 0;
}