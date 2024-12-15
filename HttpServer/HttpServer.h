#pragma once

#include <iostream>
#include <winsock2.h>



class HttpServer {
	
public:
    explicit HttpServer(std::string& host, uint16_t PORT) 
        : _host(host), _port(PORT), srv{}, socket_fd(0) {}


	void createSocket();
	void start();
	void stop();
	void exitWithError(std::string error);
	void sendResponse(SOCKET clientsocket, std::string content, std::string status, std::string contentType);
	std::string getFileContent(std::string& filepath);

	
private:
	uint16_t _port;
	std::string _host;
	sockaddr_in srv;
	int socket_fd;
	int nRet = 0;
};

