#ifndef CORE_HPP
#define CORE_HPP

#include "ECS/Manager.hpp"
#include "Engine/Event/Event.hpp"
#include "Engine/Rendering/RenderWindow.hpp"
#include "Engine/Rendering/Data.hpp"

class Core
{
    public:
        Core();
        ~Core() = default;

        void init(const std::string &_path);
        void run();

    private:
        eng::RenderWindow m_win;
        eng::Event m_event{};

        ecs::Manager m_manager{};
        // Player m_player{};
        eng::Camera m_cam;
        eng::Data m_data{};

        bool m_pause = false;
};

#endif