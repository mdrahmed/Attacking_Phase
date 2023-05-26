#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    // Create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // Bind socket to a port
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080); // Replace with your desired port

    if (bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind socket." << std::endl;
        return 1;
    }

    // Listen for connections
    if (listen(serverSocket, 1) == -1) {
        std::cerr << "Failed to listen on socket." << std::endl;
        return 1;
    }

    std::cout << "Server listening on port 8080..." << std::endl;

    // Accept and handle connections
    sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr*>(&clientAddress), &clientAddressLength);
    if (clientSocket == -1) {
        std::cerr << "Failed to accept connection." << std::endl;
        return 1;
    }

    char buffer[1024];
    std::memset(buffer, 0, sizeof(buffer));

    // Receive data from client
    if (recv(clientSocket, buffer, sizeof(buffer), 0) == -1) {
        std::cerr << "Failed to receive data." << std::endl;
        return 1;
    }

    std::string request(buffer);
    std::cout << "Received request: " << request << std::endl;

    // Send response to client
    std::string response = "Hello, client!";
    if (send(clientSocket, response.c_str(), response.length(), 0) == -1) {
        std::cerr << "Failed to send response." << std::endl;
        return 1;
    }

    // Close sockets
    //close(clientSocket);
    //close(serverSocket);

    return 0;
}

