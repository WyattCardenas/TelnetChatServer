#ifndef SERVER_H
#define SERVER_H

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <vector>

#include "Client.h"

#pragma comment (lib, "Ws2_32.lib")

class Server
{
public:
	Server(int const defaultPort);
	~Server();

	unsigned acceptNewClients();
	const Client* GetClientInfo(unsigned);
	
	std::vector<Client*> sessions;
	

private:
	SOCKET listeningSocket;
	unsigned clientCounter = 1;
	fd_set master;
	
};

#endif //SERVER_H