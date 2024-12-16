#include "http-server.h"


int main() {

	std::string host = "127.0.0.1";
	uint16_t port = 8080;

	HttpServer server(host, port);

	// Starting the server
	server.start();

	return 0;
}