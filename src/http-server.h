#pragma once

#include <iostream>
#include <winsock2.h>
#include <queue>
#include <sstream>
#include <fstream>
#include <istream>
#include <filesystem>
#include <condition_variable>
#include <mutex>
#include <thread>


class HttpServer {

public:
	explicit HttpServer(std::string& host, uint16_t PORT)
		: _host(host), _port(PORT), srv{}, socket_fd(0), stop_server(false) {
		
	}


	void createSocket();
	void start();
	void close(int socket);
	void exitWithError(std::string error);
	void createServer();
	void worker_thread();
	void sendResponse(int clientsocket, std::string content, std::string status, std::string contentType);
	std::string getFileContent(std::string& filepath);
	void generateResponce(int client_socket);



private:
	uint16_t _port;
	std::string _host;
	sockaddr_in srv;
	int socket_fd;
	std::queue<int> queue_socket;
	std::mutex mt;
	std::condition_variable cv;
	bool stop_server;



};
