#include <iostream>

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

    void BasicSocket::create()
    {
        create(socket(PF_INET, SOCK_STREAM, NULL));
    }

    void BasicSocket::create(RawSocket _socket)
    {
        m_socket = _socket;
    }

    void BasicSocket::setBlocking(bool _block)
    {
        unsigned long mode = _block;

        if (ioctlsocket(getRawSocket(), FIONBIO, &mode) != 0)
            close();
    }

    bool BasicSocket::isBlocking() const
    {
        return false;
    }

    bool BasicSocket::connect(Ip _ip, uint16_t _port, float _to)
    {
        struct addrinfo *target = nullptr;
        bool res = false;

        if (initConnect(_ip, _port, &target))
            res = selectConnect(target, _to);
        freeaddrinfo(target);
        return res;
    }

    ExitCode BasicSocket::readSome(Buffer &_buff, size_t _size)
    {
        return recv(getRawSocket(), reinterpret_cast<char *>(_buff.data()), _size, 0);
    }

    ExitCode BasicSocket::read(Buffer &_buff, size_t _size)
    {
        ExitCode readed = 0;
        ExitCode code = 0;
        Buffer buff(_size);

        while (readed != _size) {
            // bug when receiving data in the buffer
            code = readSome(buff, _size - readed);
            if (code <= 0)
                return code;
            _buff << buff;
            readed += code;
        }
        return readed;
    }

    void BasicSocket::async_readSome(Read_cb _read_cb, size_t _size)
    {
        m_tp.enqueue([this, _read_cb, _size] () {
            Buffer buff{};
            ExitCode code = this->readSome(buff, _size);

            _read_cb(buff, code);
        });
    }

    void BasicSocket::async_read(Read_cb _read_cb, size_t _size)
    {
        m_tp.enqueue([this, _read_cb, _size] () {
            Buffer buff{};
            ExitCode code = this->read(buff, _size);

            _read_cb(buff, code);
        });
    }

    ExitCode BasicSocket::write(const Buffer &_buffer)
    {
        return send(getRawSocket(), reinterpret_cast<const char *>(_buffer.data()), _buffer.size(), 0);
    }

    void BasicSocket::async_write(const Buffer &_buffer, Write_cb _write_cb)
    {
        m_tp.enqueue([this, _buffer, _write_cb] () {
            _write_cb(this->write(_buffer));
        });
    }

    BasicSocket::BasicSocket(ThreadPool &_tp, int _protocol)
        : m_tp(_tp), m_protocol(_protocol)
    {
        create();
    }

    RawSocket BasicSocket::getRawSocket() const
    {
        return m_socket;
    }

    int BasicSocket::getProtocol() const
    {
        return m_protocol;
    }

    bool BasicSocket::initConnect(const Ip &_ip, uint16_t _port, struct addrinfo **_target)
    {
        RawSocket rsocket = getRawSocket();

        m_port = _port;
        std::memset(&m_addr, 0, sizeof(struct addrinfo));
        m_addr.ai_family   = AF_INET;
        m_addr.ai_socktype = m_protocol;
        m_addr.ai_protocol = IPPROTO_TCP;
        if (getaddrinfo(_ip.c_str(), std::to_string(m_port).c_str(), &m_addr, &(*_target)) != 0) {
            std::cout << "[tcp::Socket::initConnect] error: getaddrinfo " << std::endl;
            return false;
        }
        rsocket = socket((*_target)->ai_family, (*_target)->ai_socktype, (*_target)->ai_protocol);
        if (rsocket == INVALID_SOCKET) {
            std::cout << "[tcp::Socket::initConnect] error: socket " << std::endl;
            return false;
        }
        create(rsocket);
        setBlocking(false);
        return true;
    }

    bool BasicSocket::selectConnect(struct addrinfo *_target, float _to)
    {
        RawSocket rsocket = getRawSocket();
        struct timeval to = { .tv_sec = static_cast<long>(_to), .tv_usec = 0 };
        int code = ::connect(rsocket, _target->ai_addr, _target->ai_addrlen);
        int rselect = 0;
        fd_set wset;

        if (code == 0) {
            return true;
        } else if (code == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK) {
            FD_ZERO(&wset);
            FD_SET(rsocket, &wset);
            rselect = select(static_cast<int>(rsocket) + 1, NULL, &wset, NULL, &to);
            if (rselect != 0 && rselect != SOCKET_ERROR)
                return true;
        }
        closesocket(rsocket);
        return false;
    }
}