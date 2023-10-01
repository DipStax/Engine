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
    std::ignore = _path;
}

void Core::run()
{
    eng::Event ev{};
    m_win.subscribe<eng::Event::Resize>([] (const eng::Event::Resize &_resize) {
        std::cout << "Resize callback: { height: " << _resize.height << ", width: " << _resize.width << " }" << std::endl;
    });

    m_win.subscribe<eng::Event::MouseButton>([] (const eng::Event::MouseButton &_btn) {
        std::cout << "MouseButton callback: { button: " << _btn.button << ", state: " << _btn.state << " }" << std::endl;
    });

    m_win.subscribe<eng::Event::MouseMove>([] (const eng::Event::MouseMove &_mouse) {
        std::cout << "MouseMove callback: { x: " << _mouse.x << ", y: " << _mouse.y << " }" << std::endl;
    });

    m_win.subscribe<eng::Event::Keyboard>([] (const eng::Event::Keyboard &_kb) {
        std::cout << "Keyboard callback: { key: " << _kb.key << ", state: " << _kb.state << " { shift: " << _kb.shift << ", control: " << _kb.control << ", alt: " << _kb.alt << " } }" << std::endl;
    });

    m_win.subscribe<eng::Event::Focus>([](const eng::Event::Focus& _focus) {
        std::cout << "Focus callback: { focus: " << _focus.state << " }" << std::endl;
    });

    while (m_win.isOpen()) {
        while (m_win.pollEvent(ev)) {}
        m_win.clear();
        m_win.display();
    }
}