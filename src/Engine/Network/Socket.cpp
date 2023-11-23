#include <iostream>

#include "Engine/Network/tcp/Socket.hpp"

namespace eng
{
    namespace tcp
    {
        Socket::Socket(ThreadPool &_tp)
            : BasicSocket(_tp, IPPROTO_TCP)
        {
        }
    }

    namespace udp
    {
        Socket::Socket(ThreadPool &_tp)
            : BasicSocket(_tp, IPPROTO_UDP)
        {
        }
    }
}