#pragma once

#include <limits>

#include <ws2tcpip.h>

#include "Engine/Network/Buffer.hpp"
#include "Engine/Network/Ip.hpp"
#include "Engine/Network/BasicSocket.hpp"
#include "Engine/System/ThreadPool.hpp"

namespace eng
{
    namespace tcp
    {
        class PROJECT_API Socket : public BasicSocket
        {
            public:
                Socket(ThreadPool &_tp);
                ~Socket() = default;
        };
    }

    namespace udp
    {
        class PROJECT_API Socket : public BasicSocket
        {
            public:
                Socket(ThreadPool &_tp);
                ~Socket() = default;
        };
    }
}