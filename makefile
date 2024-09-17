CXX = g++
CXXFLAGS = -std=c++11 -pthread

all: server client

server: server.cpp server.h server_main.cpp
	$(CXX) $(CXXFLAGS) -o server server.cpp server_main.cpp

client: client.cpp client.h client_main.cpp
	$(CXX) $(CXXFLAG) -o client client.cpp client_main.cpp

clean:
	rm -r server client