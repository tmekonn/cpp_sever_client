#include "client.h"

Client::Client(const std::string& server_ip, int port): port(port){
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_fd < 0){
        std::cerr << "Failed to create socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    //server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());

    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0){
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        close(client_fd);
        exit(EXIT_FAILURE);
    }
}

// void Client::sendMessage(const std::string& message){
//     sendto(client_fd, message.c_str(), message.size(), 0, 
//             (struct sockaddr *)&server_addr, sizeof(server_addr));
//     char buffer[1024] = {0};
//     recvfrom(client_fd, buffer, sizeof(buffer), 0, NULL, NULL);
    
// }

// void Client::sendMessage(const std::string& message) {
//     sendto(client_fd, message.c_str(), message.size(), 0, 
//            (struct sockaddr *)&server_addr, sizeof(server_addr));
    
//     char buffer[1024] = {0};
//     socklen_t addr_len = sizeof(server_addr);
//     int n = recvfrom(client_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &addr_len);
//     if (n < 0) {
//         std::cerr << "Receive failed" << std::endl;
//     } else {
//         std::cout << "Received response: " << buffer << std::endl;
//     }
// }

void Client::sendMessage(const std::string& message) {
    // Send the message to the server
    sendto(client_fd, message.c_str(), message.size(), 0, 
           (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    // Receive response from the server
    char buffer[1024] = {0};
    socklen_t addr_len = sizeof(server_addr);
    int n = recvfrom(client_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &addr_len);
    if (n < 0) {
        std::cerr << "Receive failed" << std::endl;
    } else {
        buffer[n] = '\0'; // Ensure null-termination of the received string
        std::cout << "[C] " << buffer << std::endl;
    }
}
