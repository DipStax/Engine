#pragma once

#include "Engine/Network/tcp/Socket.hpp"
#include "Engine/System/ThreadPool.hpp"
#include "Tool/PreProcessing.hpp"

namespace eng::tcp
{
    class PROJECT_API Acceptor
    {
        public:
            using Accept_cb = std::function<void(Socket)>;

            Acceptor(ThreadPool &_tp, uint16_t _port);
            ~Acceptor();

            bool listen(uint16_t _port);

            bool accept(Socket &_socket); // add to
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