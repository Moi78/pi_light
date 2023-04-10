#include "LightServer.h"

DMXServer::DMXServer(uint16_t port) : m_port(port), m_sigkill(false) {}

DMXServer::~DMXServer() {
    m_sigkill = false;
    close(m_socket);
}


bool DMXServer::InitServer() {
    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(m_socket == -1) {
        return false;
    }

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_addr.sin_port = htons(m_port);

    int bindRes = bind(m_socket, (sockaddr*)&m_addr, sizeof(m_addr));
    if(bindRes == -1) {
        return false;
    }

    return true;
}

void DMXServer::ProcessPackage(DMXPackage package) {

}

void DMXServer::StartServer() {
    m_dataThread = std::thread(&DMXServer::ReceiveData, this, std::ref(m_sigkill));
    m_dataThread.detach();

    bool sKill = m_sigkill.load();
    while(!sKill);
}

void DMXServer::ReceiveData(std::atomic_bool& aSigkill) {
    bool sigkill = false;

    while(!sigkill) {
        //DMXPackage pendingPackage{};
        char pendingPackage[20] = {0};

        size_t rcvSize = recvfrom(m_socket, &pendingPackage, sizeof(pendingPackage), 0, NULL, NULL);
        if(rcvSize == -1) {
            std::cout << "Error while receiving data" << std::endl;
        }

        std::cout << "Received " << rcvSize << " bytes : " << pendingPackage << std::endl;

        delete other;

        sigkill = aSigkill.load();
        std::this_thread::sleep_for(40ms);
    }
}
