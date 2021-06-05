#include "serversocket.h"
#include <netdb.h>

using namespace std;

ServerSocket::ServerSocket(string ip, uint16_t port)
{
    memset(&addr, 0, sizeof addr);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET; // IPv4

    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) != 1)
        throw SocketError("Failed to convert ip using inet_pton");

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw SocketError("Failed to get socket file descriptor");

    if (bind(socket_fd, (sockaddr *)&addr, sizeof(addr)) < 0)
        throw SocketError("Failed to bind socket");

    state_ = SocketState::DISCONNECTED;
};

void ServerSocket::waitForNewConnection()
{
    if (listen(socket_fd, 5) < 0)
        throw SocketError("Failed to listen()");

    socklen_t their_size;
    accepted_socket_fd = accept(socket_fd, (sockaddr *)&their_addr, &their_size); // wait for someone to connect - this is a blocking call
    if (accepted_socket_fd < 0)
        throw SocketError("Error accepting incoming connection");
    else
        state_ = SocketState::READY_TO_RECEIVE;
}

string ServerSocket::receiveData()
{
    if (state_ == SocketState::READY_TO_RECEIVE)
    {
        char buffer[1024] = {'\0'};
        int bytes_received = recv(accepted_socket_fd, buffer, sizeof(buffer), 0);
        if (bytes_received > 0)
            return string(buffer);
        else
            throw SocketError("Erorr receiving data from socket");
    }
    else
        throw SocketError("Socket not ready ready to receive data");
}
