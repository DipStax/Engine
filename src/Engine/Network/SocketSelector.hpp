#include "Engine/Network/SocketSelector.hpp"

namespace eng
{
    void SocketSelector::add(BasicSocket &_socket)
    {
        FD_SET(_socket.getRawSocket(), &m_read);
    }

    void SocketSelector::del(BasicSocket &_socket)
    {
        FD_CLR(_socket.getRawSocket(), &m_read);
    }

    bool isSet(BasicSocket &_socket)
    {
        return FD_ISSET(_socket.getRawSocket(), &m_read);
    }

    void SocketSelector::clear()
    {
        FD_ZERO(&m_read);
    }
}