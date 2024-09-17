#include "client.h"

int main() {
    auto start_time = std::chrono::steady_clock::now();
    int message_count = 0;
    Client client("127.0.0.1", 8080);
    
    while(true){
        message_count++;
        client.sendMessage("Message count: " + std::to_string(message_count));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
    
    return 0;
}