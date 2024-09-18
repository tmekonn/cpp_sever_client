#include "client.h"

void runClients(std::string server_ip, int port, int M){
    std::vector<std::thread> client_threads;
    for(int i = 0; i < M; i++){
        //client_threads.push_back(std::thread([server_ip, port](){
        client_threads.emplace_back(std::thread([server_ip, port](){
            Client client(server_ip, port);
            while(true){
                char buffer[1024];
                std::thread::id this_id = std::this_thread::get_id();
                snprintf(buffer, sizeof(buffer), "Message from thread %lu", std::hash<std::thread::id>{}(this_id));

                client.sendMessage(buffer);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }));
    }
    for(auto& t: client_threads){
        if(t.joinable()){
            t.join();
        }
    }
}
int main(int argc, char* argv[]) {
    int opt;
    int M =2;// default number of clients
    while((opt = getopt(argc, argv, "M:")) != -1){
        switch(opt){
            case 'M':
                M = atoi(optarg);
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " [-M <number of clients>]" << std::endl;
                //exit(EXIT_FAILURE);
                break;
        }
    }
    while(true){
        runClients("127.0.0.1", 8080, M);
    }
    
    return 0;
}