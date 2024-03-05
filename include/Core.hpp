#ifndef CORE_HPP
#define CORE_HPP

#include <string>

#include "Engine/Rendering/RenderWindow.hpp"

class Core
{
    public:
        Core();
        ~Core() = default;

        void init(const std::string &_path);
        void run();

    private:
        eng::ThreadPool m_tp;
        eng::RenderWindow m_win;
};

#endif