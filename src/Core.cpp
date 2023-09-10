#include <iostream>
#include <memory>

#include "Core.hpp"
#include "Engine/Network/tcp/Acceptor.hpp"
#include "Engine/Network/Ip.hpp"


Core::Core()
{
}

void Core::init(const std::string &_path)
{
    std::ignore = _path;

    WSADATA wsaData;
    int wsa = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (wsa != 0) {
        std::cout << "Error: wsa error: " << wsa << std::endl;
        exit(1);
    }
    m_thread = std::thread(&Core::client, this);
}

void Core::run()
{
    eng::tcp::Acceptor acceptor(m_tp, 8080);
    int val = 2593;
    eng::Buffer buff{};
    std::string str;
    eng::tcp::Socket socket(m_tp);

    acceptor.accept(socket);
    socket.read(buff, 5);

    buff >> str;
    std::cout << str << std::endl;
}

void Core::client()
{
    eng::Buffer buff{};
    eng::tcp::Socket socket(m_tp);

    if (!socket.connect(eng::Ip("127.0.0.1"), 8080)) {
        std::cerr << "Error: unable to connect to the endpoint" << std::endl;
        return;
    }
    buff << "data";
    socket.write(buff);
    while (true) {}
 }