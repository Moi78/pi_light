#ifndef PI_LIGHT_LIGHTSERVER_H
#define PI_LIGHT_LIGHTSERVER_H

#include <cstdint>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std::chrono_literals;

enum ServerCommand {
    SRV_DMX_SET,
    SRV_DMX_GET
};

struct DMXChannel {
    uint32_t universe;
    uint16_t addr;
    uint8_t data;
};

struct DMXPackage {
    ServerCommand cmd;
    uint16_t size;
    DMXChannel channels[512];
};

typedef int SOCKET;

class DMXServer {
public:
    DMXServer(uint16_t port);
    ~DMXServer();

    bool InitServer();

    void ProcessPackage(DMXPackage package);
    void StartServer();

private:
    void ReceiveData(std::atomic_bool& aSigkill);

    SOCKET m_socket;
    uint16_t m_port;

    sockaddr_in m_addr;

    std::thread m_dataThread;
    std::atomic_bool m_sigkill;
};

#endif //PI_LIGHT_LIGHTSERVER_H
