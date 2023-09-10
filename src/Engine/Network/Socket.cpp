#include "Engine/Network/Socket.hpp"

namespace eng
{
    Socket::~Socket()
    {
        close();
    }

    void Socket::close()
    {
        if (m_socket != INVALID_SOCKET)
            closesocket(m_socket);
    }

    Socket::Socket()
    {
        create(socket(PF_INET, SOCK_STREAM, NULL));
    }

    RawSocket Socket::getRawSocket() const
    {
        return m_socket;
    }

    void Socket::create()
    {
        create(socket(PF_INET, SOCK_STREAM, NULL));
    }

    void Socket::create(RawSocket _socket)
    {
        m_socket = _socket;
    }
}