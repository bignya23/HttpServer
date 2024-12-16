#include "http-server.h"
#include <sstream>
#include <fstream>
#include <istream>
#include <filesystem>
#include <condition_variable>
#include <mutex>
#include <thread>


// For Error Handeling
void HttpServer::exitWithError(std::string error) {
	std::cerr << "Error: " << error << std::endl;
	exit(EXIT_FAILURE);
}


// Creating Server Socket
void HttpServer::createSocket() {
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		exitWithError("Socket Creation Failed");
	}
}


// Sends Responce to the client
void HttpServer::sendResponse(int clientsocket, std::string content,  std::string status, std::string contentType) {

	std::ostringstream response;

	response << "HTTP/1.1 " << status << "\n";
	response << "Content-Type: " << contentType << "\n";
	response << "Content-Length: " << content.size() << "\n";
	response << "Connection: close\r\n\r\n";
	response << content;

	send(clientsocket, response.str().c_str(), response.str().length(), 0);

	close(clientsocket);
}

void HttpServer::generateResponce(int client_socket) {

	char buff[1024] = { 0 };
	recv(client_socket, buff, sizeof(buff), 0);
	std::string request(buff);


	std::istringstream requestStream(request);
	std::string method, filePath;
	requestStream >> method >> filePath;

	std::cout << "Client Connected\n";
	if (method == "GET") {
		if (filePath == "/") filePath = "/index.html";
		filePath = filePath.substr(1);

		std::string content = getFileContent(filePath);
		sendResponse(client_socket, content, "200 OK", "text/html");
	}

}


std::string HttpServer::getFileContent(std::string& filepath) {


	//std::cout << std::filesystem::current_path();

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

// Server Creation
void HttpServer::createServer() {

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) < 0) {
		exitWithError("Wsa startup failed");
	}

	// Socket Creation
	createSocket();

	// Declare environment variables
	srv.sin_family = AF_INET;
	srv.sin_port = htons(_port);
	srv.sin_addr.s_addr = inet_addr(_host.c_str());
	memset(&srv.sin_zero, 0, 8);

	// Binding
	if (bind(socket_fd, (sockaddr*)&srv, sizeof(sockaddr)) < 0) {
		WSACleanup();
		exitWithError("Binding failed");
	}

	//Listening
	if (listen(socket_fd, 5) < 0) {
		WSACleanup();
		exitWithError("Listening Failed!!!");
	}

	std::cout << "Server started on Address : " << _host << ", PORT : " << _port << std::endl;
}


void HttpServer::worker_thread() {
	while (true) {
		int client_socket;
		{
			std::unique_lock<std::mutex> lock(mt);

			cv.wait(lock, [this] {return !queue_socket.empty() || stop_server; }); // Waiting for something to there in the queue/ stopserver is true

			if (queue_socket.empty() || stop_server) {
				break;
			}
			client_socket = queue_socket.front();
			queue_socket.pop();
		}

		generateResponce(client_socket);


	}
}

void HttpServer::start() {

	// Creating the server
	createServer();

	// Thread Pool
	const int threads_count = 5;
	std::vector<std::thread> threads(threads_count);

	for (size_t i = 0; i < threads_count; i++) {
		threads.emplace_back(&HttpServer::worker_thread, this);
	}


	while (true) {
		int clientSocket = accept(socket_fd, NULL, NULL);
		if (clientSocket < 0) {
			exitWithError("Client socket creation failed");
		}

		{
			std::lock_guard<std::mutex> lock(mt);
			queue_socket.push(clientSocket);
		}
		cv.notify_one();
	}

	{
		std::lock_guard <std::mutex> lock(mt);
		stop_server = true;
		cv.notify_all();
	}

	// Joining the threads
	for (auto& it : threads) {
		if (it.joinable()) {
			it.join();
		}
	}

	close(socket_fd);

}


// Closing the Socket
void HttpServer::close(int socket) {
	closesocket(socket);
	std::cout << "Socket Closed" << std::endl;
}

