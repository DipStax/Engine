#include <string>

#include <ws2tcpip.h>

#include "Engine/Network/tcp/Acceptor.hpp"

namespace eng::tcp
{
    Acceptor::Acceptor(ThreadPool &_tp, uint16_t _port)
        : m_tp(_tp), m_port(_port), m_tcpsocket(m_tp)
    {
        listen(m_port);
    }

    Acceptor::~Acceptor()
    {
        stop();
    }

    bool Acceptor::listen(uint16_t _port)
    {
        struct addrinfo *ep = NULL;
        struct addrinfo sin;

        stop();
        m_port = _port;
        std::memset(&sin, 0, sizeof(struct addrinfo));
        sin.ai_family = AF_INET;
        sin.ai_socktype = SOCK_STREAM;
        sin.ai_protocol = IPPROTO_TCP;
        sin.ai_flags = AI_PASSIVE;
        if (getaddrinfo(NULL, std::to_string(m_port).c_str(), &sin, &ep))
            return false;
        m_socket = socket(ep->ai_family, ep->ai_socktype, ep->ai_protocol);
        if (m_socket == INVALID_SOCKET) {
            freeaddrinfo(ep);
            return false;
        }
        if (bind(m_socket, ep->ai_addr, (int)ep->ai_addrlen) == -1) {
            freeaddrinfo(ep);
            closesocket(m_socket);
            m_socket = INVALID_SOCKET;
            return false;
        }
        freeaddrinfo(ep);
        if (::listen(m_socket, SOMAXCONN) == -1) {
            closesocket(m_socket);
            m_socket = INVALID_SOCKET;
            return false;
        }
        return true;
    }

    bool Acceptor::accept(Socket &_socket)
    {
        RawSocket target = INVALID_SOCKET;
        sockaddr_in addr;
        int len = sizeof(sockaddr_in);

        _socket.close();
        if (m_socket == INVALID_SOCKET)
            return false;
        target = ::accept(m_socket, reinterpret_cast<sockaddr *>(&addr), &len);
        if (target == INVALID_SOCKET)
            return false;
        _socket.create(target);
        return true;
    }

    void Acceptor::async_accept(Accept_cb _accept_cb)
    {
        m_tp.enqueue([this, _accept_cb]() {
            Socket socket(this->m_tp);

            if (!accept(socket))
                this->async_accept(_accept_cb);
            else
                _accept_cb(socket);
        });
    }

    void Acceptor::stop()
    {
        closesocket(m_socket);
    }
}