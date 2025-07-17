#ifndef __INETADDRESS__
#define __INETADDRESS__

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>


namespace muduo{
    // 封装 socket_in 
    class InetAddress {
    public:
        // 打包 ip 地址和端口
        explicit InetAddress(uint16_t port, std::string ip = "127.0.0.1");
        explicit InetAddress(const sockaddr_in& other) : m_addr(other) {}

        std::string toIp() const;   
        uint16_t toPort() const;
        std::string toIpPort() const;

        const sockaddr_in *getSockAddr() { return &m_addr; };

    private:
        sockaddr_in m_addr;
    };
}


#endif