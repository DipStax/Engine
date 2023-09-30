#include <iostream>
#include <sstream>

#include "Core.hpp"
#include "XML/Builder.hpp"

Core::Core()
    : m_tp(), m_win(m_tp, 300, 300, "title")
{
}

void Core::init(const std::string &_path)
{
}

void Core::run()
{
    eng::Event ev{};

    while (m_win.isOpen()) {
        while (m_win.pollEvent(ev)) {}
        m_win.clear();
        m_win.display();
    }
}