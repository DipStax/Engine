#include <iostream>

#include "Engine/Rendering/Loader.hpp"
#include "Core.hpp"
#include "Engine/Rendering/Sprite.hpp"

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
    eng::RenderTexture rdtxtr;
    eng::Sprite sprt;
    eng::Sprite sprt2;
    eng::Texture txtr;

    std::cout << "Texture for sprite" << std::endl;
    sprt.setTexture(*(m_data.Texture.at(1)));
    for (uint32_t y = 0; y < 5; y++) {
        for (uint32_t x = 0; x < 5; x++) {
            std::cout << m_data.Texture.at(1)->getPixel({ x, y }) << " ";
        }
        std::cout << std::endl;
    }
    rdtxtr.create(50, 50);
    rdtxtr.draw(sprt);
    txtr = rdtxtr.getTexture();
    sprt.setPosition(0, 150);
    sprt.setScale(1.5, 1.5);
    //sprt.setTxtrRect(eng::Rect{ { 0, 0 }, { 5, 5 } });
    sprt2.setTexture(txtr); // tri range bug
    // m_player.setComponent(m_manager, 1);
    while (m_win.isOpen()) {
        while (m_win.pollEvent(m_event)) {}
        if (!m_pause) {
            m_win.clear();
            //for (auto &[_, _mod] : m_data.Model)
            //    m_win.draw(*_mod);
             // m_manager.runSystem<ecs::sys::RenderModel>(nullptr, &m_win);
            m_win.draw(sprt2);
            m_win.draw(sprt);
            m_win.display();
            m_win.setSize(500, 500);
        }
    }
}