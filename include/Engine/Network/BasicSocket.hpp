#pragma once

#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")

#include "Tool/Export.hpp"

namespace eng
{
    using RawSocket = SOCKET;
    using ExitCode = int;

    namespace tcp
    {
        class Acceptor;
    }

    class PROJECT_API BasicSocket
    {
        public:
            virtual ~BasicSocket();

            void close();

        protected:
            friend tcp::Acceptor;

            BasicSocket();

            [[nodiscard]] RawSocket getRawSocket() const;

            void create();
            void create(RawSocket _socket);

        private:
            RawSocket m_socket = INVALID_SOCKET;
    };
}