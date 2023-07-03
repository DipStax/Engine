#ifndef CORE_HPP
#define CORE_HPP

#include "Engine/Window.hpp"
#include "ECS/Manager.hpp"
#include "Player.hpp"
#include "Engine/Ressource/Data.hpp"

class Core
{
    public:
        Core();
        ~Core() = default;

        void init(const std::string &_path);
        void run();

    protected:
        void pollEvent();

    private:
        eng::Window m_win;
        sf::Event m_event{};

        ecs::Manager m_manager{};
        Player m_player{};
        eng::Data m_data{};

        bool m_pause = false;
};

#endif