#include <iostream>

#include <SFML/Graphics.hpp>

#include "Engine/Ressource/Loader.hpp"
#include "Core.hpp"

Core::Core()
    : m_win({ 400, 400 }, "Test ECS")
{
}

void Core::init(const std::string &_path)
{
    eng::Loader loader;
    ecs::Component &player = m_manager.get(m_manager.spawn());

    std::cout << "[Core] Init - End" << std::endl;
    m_data = loader.load(_path);
    opt::get<ecs::comp::Id>(player).emplace(1);
    opt::get<ecs::comp::Model>(player).emplace(ecs::comp::Model{ .mod = m_data.Model.at(1)->copy() });
    m_win.setCamera(110, { 0.1, 100});
    std::cout << "[Core] Init - Done" << std::endl;
}

void Core::run()
{

    m_player.setComponent(m_manager, 1);
    while (m_win.isOpen()) {
        pollEvent();
        if (!m_pause) {
            m_win.clear(sf::Color::White);
            m_manager.runSystem<ecs::sys::RenderModel>(nullptr, &m_win);
            m_win.render();
        }
    }
}

void Core::pollEvent()
{
    while (m_win.pollEvent(m_event)) {
        if (m_event.type == sf::Event::EventType::Closed)
            m_win.close();
        else
            m_player.eventHandle(m_event, m_manager);
        if (m_event.type == sf::Event::EventType::KeyPressed) {
            switch (m_event.key.code) {
                // move
                case sf::Keyboard::Z:
                    m_win.moveCamera({ 0, 0, 0.1 });
                    break;
                case sf::Keyboard::S:
                    m_win.moveCamera({ 0, 0, -0.1 });
                    break;
                case sf::Keyboard::D:
                    m_win.moveCamera({ 0.1, 0, 0 });
                    break;
                case sf::Keyboard::Q:
                    m_win.moveCamera({ -0.1, 0, 0 });
                    break;
                case sf::Keyboard::A:
                    m_win.moveCamera({ 0, 0.1, 0 });
                    break;
                case sf::Keyboard::E:
                    m_win.moveCamera({ 0, -0.1, 0 });
                    break;

                // rotation
                case sf::Keyboard::R:
                    m_win.rotateCamera({ 1, 0, 0 });
                    break;
                case sf::Keyboard::F:
                    m_win.rotateCamera({ -1, 0, 0 });
                    break;
                case sf::Keyboard::T:
                    m_win.rotateCamera({ 0, 1, 0 });
                    break;
                case sf::Keyboard::G:
                    m_win.rotateCamera({ 0, -1, 0 });
                    break;
                case sf::Keyboard::Y:
                    m_win.rotateCamera({ 0, 0, 1 });
                    break;
                case sf::Keyboard::H:
                    m_win.rotateCamera({ 0, 0, -1 });
                    break;

                case sf::Keyboard::P:
                    m_pause = !m_pause;
                    break;
            }
        }
    }
}