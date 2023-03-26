#ifndef PI_LIGHT_LIGHTSERVER_H
#define PI_LIGHT_LIGHTSERVER_H

#include <cstdint>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

enum ServerCommand {
    SRV_DMX_SET,
    SRV_DMX_GET
};

class DMXServer {
public:
    DMXServer(uint16_t port);
    ~DMXServer() = default;

    bool InitServer();

    void ProcessPackage(uint64_t package);

private:
    SOCKET m_socket;

    uint16_t m_port;
};

#endif //PI_LIGHT_LIGHTSERVER_H
