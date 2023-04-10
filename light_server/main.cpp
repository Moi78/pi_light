#include <iostream>

#include "LightServer.h"

int main(int argc, char** argv) {
    DMXServer server{5000};

    if(!server.InitServer()) {
        std::cerr << "Failed to init server" << std::endl;
        return -1;
    } else {
        std::cout << "Server listening on port " << 5000 << std::endl;
    }

    server.StartServer();

    return 0;
}