#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <chrono>
#include <thread>
#include <vector>

class Client {
public:
    Client(const std::string& server_ip, int port);
    void sendMessage(const std::string& message);

private:
    int port;
    int client_fd;
    struct sockaddr_in server_addr;
};

#endif // CLIENT_H