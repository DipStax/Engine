#pragma once

#include <limits>

#include <ws2tcpip.h>

#include "Engine/Network/Buffer.hpp"
#include "Engine/Network/Ip.hpp"
#include "Engine/Network/Socket.hpp"
#include "Engine/System/ThreadPool.hpp"

namespace eng::tcp
{
    class PROJECT_API Socket : public ::eng::Socket
    {
        public:
            using Read_cb = std::function<void(Buffer &, ExitCode)>;
            using Write_cb = std::function<void(ExitCode)>;

            Socket(ThreadPool &_tp);
            ~Socket() = default;

            void setBlocking(bool _block);

            [[nodiscard]] bool isBlocking() const;

            bool connect(Ip _ip, uint16_t _port, float _to = 0.f);

            ExitCode readSome(Buffer &_buff, size_t _size = std::numeric_limits<size_t>::max());
            ExitCode read(Buffer &_buff, size_t _size);
            // how to trigger the async at the right timing?
            void async_readSome(Read_cb _read_cb, size_t _size = std::numeric_limits<size_t>::max());
            void async_read(Read_cb _read_cb, size_t _size);

            ExitCode write(const Buffer &_buffer);
            void async_write(const Buffer &_buffer, Write_cb _write_cb);

            void close();

        private:
            bool initConnect(const Ip &_ip, uint16_t _port, struct addrinfo **target);
            bool selectConnect(struct addrinfo *target, float _to);

            ThreadPool &m_tp;

            uint16_t m_port;
            struct addrinfo m_addr;
    };
}