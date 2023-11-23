#pragma once

#include <functional>
#include <type_traits>

#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")

#include "Engine/Network/Buffer.hpp"
#include "Engine/Network/Ip.hpp"
#include "Engine/System/ThreadPool.hpp"
#include "Tool/Export.hpp"

namespace eng
{
    using RawSocket = SOCKET;
    using ExitCode = int;

    class BasicSocket;

    template<class T>
    concept IsBaseSocket = std::is_base_of_v<T, eng::BasicSocket>;

    class PROJECT_API BasicSocket
    {
        public:
            using Read_cb = std::function<void(Buffer &, ExitCode)>;
            using Write_cb = std::function<void(ExitCode)>;

            virtual ~BasicSocket();

            bool connect(Ip _ip, uint16_t _port, float _to = 0.f);
            void close();

            void setBlocking(bool _block);
            [[nodiscard]] bool isBlocking() const;

            ExitCode readSome(Buffer &_buff, size_t _size = std::numeric_limits<size_t>::max());
            ExitCode read(Buffer &_buff, size_t _size);

            // how to trigger the async at the right timing?
            void async_readSome(Read_cb _read_cb, size_t _size = std::numeric_limits<size_t>::max());
            void async_read(Read_cb _read_cb, size_t _size);

            ExitCode write(const Buffer &_buffer);
            void async_write(const Buffer &_buffer, Write_cb _write_cb);

        protected:
            template<IsBaseSocket T>
            friend class Acceptor;

            BasicSocket(ThreadPool &_tp, int _protocol);

            [[nodiscard]] int getProtocol() const;
            [[nodiscard]] RawSocket getRawSocket() const;

            void create();
            void create(RawSocket _socket);

        private:
            bool initConnect(const Ip &_ip, uint16_t _port, struct addrinfo **_target);
            bool selectConnect(struct addrinfo *target, float _to);

            ThreadPool &m_tp;

            uint16_t m_port;
            struct addrinfo m_addr;
            const int m_protocol;

            RawSocket m_socket = INVALID_SOCKET;
    };
}