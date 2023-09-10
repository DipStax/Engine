#pragma once

#include <vector>

#include "Engine/Network/BasicSocket.hpp"

namespace eng
{
    class PROJECT_API SocketSelector
    {
        public:
            SocketSelector() = default;
            ~SocketSelector() = default;

            void add(BasicSocket &_socket);
            void del(BasicSocket &_socket);

            [[nodiscard]] bool isSet(BasicSocket &_socket);

            void clear();

        private:
            FD_SET m_read;
    };
}