#include "HttpServer.h"
#include <sstream>
#include <fstream>
#include <istream>

void HttpServer::exitWithError(std::string error) {
	std::cerr << "Error: " << error << std::endl;
	exit(EXIT_FAILURE);
}

void HttpServer::sendResponse(SOCKET clientsocket, std::string content, std::string status, std::string contentType) {

	std::ostringstream response;

	response << "HTTP/1.1 " << status << "\n";
	response << "Content-Type: " << contentType << "\n";
	response << "Content-Length: " << content.size() << "\n";
	response << "Connection: close\r\n\r\n";
	response << content;

	send(clientsocket, response.str().c_str(), response.str().length(), 0);
}

std::string HttpServer::getFileContent(std::string& filepath) {
	
	
	std::ifstream file(filepath);

	if (!file.is_open()) {
		exitWithError("File not found : " + filepath);
	}

	std::string content{};
	
	{
		std::stringstream filecontents;
		std::fstream file(filepath, std::ios::in);
		filecontents << file.rdbuf();
		
		content = filecontents.str();
	}

	return content;
	
}


void HttpServer::start() {

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) < 0) {
		exitWithError("Wsa startup failed");
	}

	// Socket Creation
	createSocket();

	// Declare environment variables
	srv.sin_family = AF_INET;
	srv.sin_port = htons(_port);
	srv.sin_addr.s_addr = INADDR_ANY;
	memset(&srv.sin_zero, 0, 8);

	// Binding
	nRet = bind(socket_fd, (sockaddr*)&srv, sizeof(sockaddr));
	if (nRet < 0) {
		WSACleanup();
		exitWithError("Binding failed");
	}

	//Listening
	if (listen(socket_fd, 5) < 0) {
		WSACleanup();
		exitWithError("Listening Failed!!!");
	}

	std::cout << "Server started on Address : " << _host << " , PORT : " << _port << std::endl;


	while (true) {
		SOCKET clientSocket = accept(socket_fd, NULL, NULL);
		if (clientSocket < 0) {
			exitWithError("Client socket creation failed");
		}
		char buff[1024] = { 0 };
		recv(clientSocket, buff, sizeof(buff), 0);
		std::string request(buff);



		std::istringstream requestStream(request);
		std::string method, filePath;
		requestStream >> method >> filePath;

		std::cout << "Client Connected\n";
		if (method == "GET") {
			if (filePath == "/") filePath = "/index.html";
			filePath = filePath.substr(1);

			std::string content = getFileContent(filePath);
			sendResponse(clientSocket, content, "200 OK", "text/html");
		}
	}
}

void HttpServer::stop() {
	closesocket(socket_fd);
}

void HttpServer::createSocket() {
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		exitWithError("Socket Creation Failed"); 
	}
}
