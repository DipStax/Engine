#include "Player.hpp"

Player::Player()
{
    Init();
}

void Player::eventHandle(sf::Event &_event, ecs::Manager &_manager)
{
    if (!m_comp)
        return;
    if (m_event.contains(_event.type))
        (this->*(m_event[_event.type]))(_event);
}

void Player::setComponent(ecs::Manager &_manager, uint32_t _id)
{
    ecs::Entity::IdType entityId = 0;

    if (_id != 0)
        m_id = _id;
    entityId = _manager.find<ecs::comp::Id>([this] (const std::optional<ecs::comp::Id> &_id) {
        return _id.has_value() && _id.value().Id == m_id;
    });
    if (entityId != 0)
        return;
    m_comp = &_manager.get(entityId);
}

void Player::Init()
{
    static bool init = false;

    if (init)
        return;
    init = true;
    m_event[sf::Event::KeyPressed] = &Player::event_KeyPressed;
    m_event[sf::Event::KeyReleased] = &Player::event_KeyReleased;
}

void Player::event_KeyPressed(sf::Event &_event)
{
    std::optional<ecs::comp::Velocity> opt_velo = opt::get<ecs::comp::Velocity>(*m_comp);
    ecs::comp::Velocity velo;
    ecs::comp::Velocity newVelo;

    if (!opt_velo.has_value())
        return;
    velo = opt_velo.value();
    if (_event.key.code == sf::Keyboard::Space && velo.y != 0) {
        velo.y = 0.2;
    } else if (FN_EVENTKEY_DIR(_event)) {
        newVelo = processVelocity(_event);
        velo = { newVelo.x, velo.y, newVelo.z };
    }
    opt_velo.emplace(processVelocity(_event));
}

void Player::event_KeyReleased(sf::Event &_event)
{
    std::optional<ecs::comp::Velocity> opt_velo = opt::get<ecs::comp::Velocity>(*m_comp);
    ecs::comp::Velocity velo;
    ecs::comp::Velocity newVelo;

    if (!opt_velo.has_value())
        return;
    velo = opt_velo.value();
    switch (_event.key.code) {
        case sf::Keyboard::Z:;
        case sf::Keyboard::S: velo.z = 0;
            break;
        case sf::Keyboard::Q:
        case sf::Keyboard::D: velo.x = 0;
            break;
    }
    opt_velo.emplace(velo);
}

ecs::comp::Velocity Player::processVelocity(sf::Event &_event) const
{
    ecs::comp::Velocity velo;

    if (_event.key.code == sf::Keyboard::Z)
        velo = { 0, 0, -1 };
    else if (_event.key.code == sf::Keyboard::S)
        velo = { 0, 0, 1 };
    else if (_event.key.code == sf::Keyboard::D)
        velo = { 1, 0, 0 };
    else if (_event.key.code == sf::Keyboard::Q)
        velo = { -1, 0, 0 };
    return velo;
}