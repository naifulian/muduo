#include <strings.h> // for func bzero
#include <cstring>

#include "InetAddress.h"

muduo::InetAddress::InetAddress(uint16_t port, std::string ip) {
    bzero(&m_addr, sizeof(m_addr));
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    m_addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

std::string muduo::InetAddress::toIp() const{
    char buf[64] = {0};
    inet_ntop(AF_INET, &m_addr.sin_addr, buf, sizeof(buf));
    return buf;
}

uint16_t muduo::InetAddress::toPort() const {
    return ntohs(m_addr.sin_port);
}

std::string muduo::InetAddress::toIpPort() const {
    char buf[64] = {0};
    inet_ntop(AF_INET, &m_addr.sin_addr, buf, sizeof(buf));
    size_t end = strlen(buf);
    uint16_t port = ntohs(m_addr.sin_port);
    sprintf(buf + end, ":%u", port);
    return buf;
}



