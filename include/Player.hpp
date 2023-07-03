#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Event.hpp>

#include "ECS/Manager.hpp"

class Player
{
    public:
        Player();
        ~Player() = default;

        void setComponent(ecs::Manager &_manager, uint32_t _id = 0);

        void eventHandle(sf::Event &_event, ecs::Manager &_manager);

    protected:
        using FnEvent = void (Player::*)(sf::Event &);

        static void Init();
        static inline std::map<sf::Event::EventType, FnEvent> m_event;

        void event_KeyPressed(sf::Event &_event);
        void event_KeyReleased(sf::Event &_event);

        [[nodiscard]] ecs::comp::Velocity processVelocity(sf::Event &_event) const;

    private:
        uint32_t m_id = 0;
        ecs::Component *m_comp = nullptr;
};

#define FN_EVENTKEY_DIR(_event)             \
    _event.key.code == sf::Keyboard::Z ||   \
    _event.key.code == sf::Keyboard::S ||   \
    _event.key.code == sf::Keyboard::D ||   \
    _event.key.code == sf::Keyboard::Q

#define GEN_FN_KEYPRESSED                          \
    sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || \
    sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || \
    sf::Keyboard::isKeyPressed(sf::Keyboard::S) || \
    sf::Keyboard::isKeyPressed(sf::Keyboard::D)

#endif