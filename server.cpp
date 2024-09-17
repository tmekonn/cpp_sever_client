#include "server.h"

static int response_count = 0;
// implement server member functions 
Server::Server(int port) : port(port){
    server_fd = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM is for UDP
                                                // SOCK_STREAM is for TCP
    if(server_fd < 0){
        std::cerr << "Failed to create socket" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    if(bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        std::cerr << "Failed to bind socket" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

}

void Server::start() {
    while (true) {
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        char buffer[1024] = {0};

        int n = recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_address, &client_len);
        if (n < 0) {
            std::cerr << "Receive failed" << std::endl;
            continue;
        }

        std::cout << "[S] " << buffer << std::endl;
        client_threads.emplace_back(&Server::handleClients, this, client_address, server_fd);

        //std::thread client_thread(&Server::handleClients, this, client_address, server_fd);
        //client_threads.push_back(std::move(client_thread));
    }

    for (auto& t : client_threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

// void Server::handleClients(struct sockaddr_in client_address, int server_fd){
//     char response[] = "Message received";
//     sendto(server_fd, response, strlen(response), 0, 
//             (struct sockaddr *)&client_address, sizeof(client_address));
// }

void Server::handleClients(struct sockaddr_in client_address, int server_fd) {
    response_count++;
    char response[1024];
    memset(response, 0, sizeof(response));
    char message[] = "Message received";
    snprintf(response, sizeof(response), "%s %d", message, response_count);
    int n = sendto(server_fd, response, strlen(response), 0, 
                   (struct sockaddr *)&client_address, sizeof(client_address));
    if (n < 0) {
        std::cerr << "Send failed" << std::endl;
    }
}