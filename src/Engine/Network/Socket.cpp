#include "Engine/Network/Socket.hpp"

namespace eng
{
    BasicSocket::~Socket()
    {
        close();
    }

    void BasicSocket::close()
    {
        if (m_socket != INVALID_SOCKET)
            closesocket(m_socket);
    }

    BasicSocket::BasicSocket()
    {
        create(socket(PF_INET, SOCK_STREAM, NULL));
    }

    RawSocket BasicSocket::getRawSocket() const
    {
        return m_socket;
    }

    void BasicSocket::create()
    {
        create(socket(PF_INET, SOCK_STREAM, NULL));
    }

    void BasicSocket::create(RawSocket _socket)
    {
        m_socket = _socket;
    }
}