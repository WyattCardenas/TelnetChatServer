#ifndef CLIENTS_H
#define CLIENTS_H

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <string>

class Client
{
public:
	Client(unsigned, SOCKET, sockaddr_in);
	~Client();

	int GetClientMessageSize();
	SOCKET GetSocket() const;

	unsigned GetClientId() const;
	const char* GetClientIpAddr() const;

private:
	SOCKET socket;
	sockaddr_in addr;
	std::string nickname;
	unsigned connectionId;

	
};

#endif
