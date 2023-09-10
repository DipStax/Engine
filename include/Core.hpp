#ifndef CORE_HPP
#define CORE_HPP

#include "Engine/System/ThreadPool.hpp"
#include "Engine/Network/tcp/Socket.hpp"

class Core
{
    public:
        Core();
        ~Core() = default;

        void init(const std::string &_path);
        void run();

        void client();

    private:
        eng::ThreadPool m_tp;
        std::unique_ptr<eng::tcp::Socket> m_socket = nullptr;
        std::thread m_thread;
};

#endif