#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>  // inet_pton
#include <netinet/in.h> // sockaddr_in
#include <exception>
#include <string>
#include <string.h>
#include <unistd.h>

struct SocketError : public std::exception
{
    SocketError(std::string info) : info(info) {}
    std::string info;
    const char *what() const noexcept
    {
        return info.c_str();
    }
};

enum class SocketState { DISCONNECTED, READY_TO_RECEIVE };

class ServerSocket
{
public:
    ServerSocket(std::string ip, uint16_t port);
    void waitForNewConnection();
    std::string receiveData();

private:
    struct sockaddr_in addr;
    struct sockaddr_in their_addr;
    int socket_fd;
    int accepted_socket_fd;

    SocketState state_;
};