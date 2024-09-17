#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

class Server {
    public:
        Server(int port);
        void start();
    private:
        int port;
        int server_fd;
        struct sockaddr_in server_address;
        std::vector<std::thread> client_threads;
        std::mutex mtx;

        void handleClients(struct sockaddr_in client_address, int server_fd);
};
#endif // SERVER_H