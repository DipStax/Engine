#pragma once

#include "Engine/Network/BasicSocket.hpp"
#include "Engine/System/ThreadPool.hpp"
#include "Tool/PreProcessing.hpp"

namespace eng::tcp
{
    template<IsBaseSocket T>
    class PROJECT_API Acceptor
    {
        public:
            using Accept_cb = std::function<void (T)>;

            Acceptor(ThreadPool &_tp, uint16_t _port);
            ~Acceptor();

            bool listen(uint16_t _port);

            bool accept(T &_socket);
            void async_accept(Accept_cb _fb);

            void stop();

        private:
            ThreadPool &m_tp;
            uint16_t m_port;

            RawSocket m_socket;
            Socket m_tcpsocket;


            bool m_wait;
    };
}