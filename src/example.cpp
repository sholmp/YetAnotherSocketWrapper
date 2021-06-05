#include "serversocket.h"

#include <fmt/format.h>
#include <fmt/color.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    string ip = "127.0.0.1";
    uint16_t port = 1337;

    try
    {
        ServerSocket server_socket(ip, port);
        server_socket.waitForNewConnection();
        while (true)
        {
            string data = server_socket.receiveData();
            fmt::print(fg(fmt::color::spring_green), "Received data: {}", data);
        }
    }
    catch (const std::exception &e)
    {
        fmt::print(fg(fmt::color::red), "{}", e.what());
    }

    return 0;
}