#include <iostream>
#include <sstream>

#include "Core.hpp"
#include "XML/Builder.hpp"

Core::Core()
    : m_tp(), m_sys_ep(m_tp), m_xml(m_tp, m_sys_ep), m_win(m_tp, 300, 300, "title")
{
}

void Core::init(const std::string &_path)
{
    std::ignore = _path;

    m_win.subscribe<eng::Event::Resize>([this] (const eng::Event::Resize &_resize) {
        m_sys_ep.template raise<eng::Event::Resize>(_resize);
        std::cout << "Resize callback: { height: " << _resize.height << ", width: " << _resize.width << " }" << std::endl;
    });

    m_win.subscribe<eng::Event::MouseButton>([this] (const eng::Event::MouseButton &_btn) {
        m_sys_ep.template raise<eng::Event::MouseButton>(_btn);
        std::cout << "MouseButton callback: { button: " << _btn.button << ", state: " << _btn.state << " }" << std::endl;
    });

    m_win.subscribe<eng::Event::MouseMove>([this] (const eng::Event::MouseMove &_mouse) {
        m_sys_ep.template raise<eng::Event::MouseMove>(_mouse);
        std::cout << "MouseMove callback: { x: " << _mouse.x << ", y: " << _mouse.y << " }" << std::endl;
    });

    m_win.subscribe<eng::Event::Keyboard>([this] (const eng::Event::Keyboard &_kb) {
        m_sys_ep.template raise<eng::Event::Keyboard>(_kb);
        std::cout << "Keyboard callback: { key: " << _kb.key << ", state: " << _kb.state << " { shift: " << _kb.shift << ", control: " << _kb.control << ", alt: " << _kb.alt << " } }" << std::endl;
    });

    m_win.subscribe<eng::Event::Focus>([this](const eng::Event::Focus& _focus) {
        m_sys_ep.template raise<eng::Event::Focus>(_focus);
        std::cout << "Focus callback: { focus: " << _focus.state << " }" << std::endl;
    });
}

void Core::run()
{
    eng::Event ev{};

    while (m_win.isOpen()) {
        while (m_win.pollEvent(ev)) {}
        m_win.clear();
        m_xml.display();
        m_win.draw(m_xml);
        m_win.display();
    }
}