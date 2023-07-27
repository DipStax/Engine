#include <iostream>

#include "Engine/Rendering/Loader.hpp"
#include "Core.hpp"

Core::Core()
    : m_win(400, 400, "Test ECS")
{
}

void Core::init(const std::string &_path)
{
    eng::Loader loader;
    //ecs::Component &player = m_manager.get(m_manager.spawn());

    std::cout << "[Core] Init - End" << std::endl;
    m_data = loader.load(_path);
    // opt::get<ecs::comp::Id>(player).emplace(1);
    // opt::get<ecs::comp::Model>(player).emplace(ecs::comp::Model{ .mod = m_data.Model.at(1)->copy() });
    m_win.setCamera(110.f, { 0.1f, 100.f});
    std::cout << "[Core] Init - Done" << std::endl;
}

void Core::run()
{
    // m_player.setComponent(m_manager, 1);
    while (m_win.isOpen()) {
        while (m_win.pollEvent(m_event)) {}
        if (!m_pause) {
            m_win.clear();
            for (auto &[_, _mod] : m_data.Model)
                m_win.draw(*_mod);
            // m_manager.runSystem<ecs::sys::RenderModel>(nullptr, &m_win);
            m_win.display();
        }
    }
}