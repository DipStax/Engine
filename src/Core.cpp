#include "Engine/Rendering/Loader.hpp"
#include "Engine/Rendering/Sprite.hpp"
#include "Engine/Rendering/RenderTexture.hpp"
#include "Core.hpp"

Core::Core()
    : m_win(400, 400, "Test ECS")
{
}

void Core::init(const std::string &_path)
{
    eng::Loader loader;
    //ecs::Component &player = m_manager.get(m_manager.spawn());

    m_data = loader.load(_path);
    // opt::get<ecs::comp::Id>(player).emplace(1);
    // opt::get<ecs::comp::Model>(player).emplace(ecs::comp::Model{ .mod = m_data.Model.at(1)->copy() });

}

void Core::run()
{
    eng::Sprite sprt;
    eng::Model model = m_data.Model.at(1)->copy();

    sprt.setPosition(0, 150);
    //sprt.setScale(1.5, 1.5);
    sprt.setTexture(*(m_data.Texture.at(1)));
    while (m_win.isOpen()) {
        while (m_win.pollEvent(m_event)) {}
        if (!m_pause) {
            m_win.clear();
            //for (auto &[_, _mod] : m_data.Model)
            //    m_win.draw(*_mod);
             // m_manager.runSystem<ecs::sys::RenderModel>(nullptr, &m_win);
            m_win.draw(sprt);
            m_win.draw(model);
            m_win.display();
        }
    }
}