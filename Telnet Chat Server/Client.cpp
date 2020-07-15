#include "Client.h"

Client::Client(unsigned connectionId, SOCKET socket, sockaddr_in addr)
{
	this->socket = socket;
	this->addr = addr;
	this->connectionId = connectionId;

	nickname = "GuestNNN";
}

Client::~Client()
{
}

int Client::GetClientMessageSize()
{
	return 0;
}

SOCKET Client::GetSocket() const
{
	return socket;
}

unsigned Client::GetClientId() const
{
	return connectionId;
}

const char* Client::GetClientIpAddr() const
{
	char* ipAddr = new char[17];
	return inet_ntop(AF_INET, &addr.sin_addr, ipAddr, 17);
}
