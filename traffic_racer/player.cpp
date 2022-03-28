//
// Created by Кирилл Галимзянов on 11.03.2022.
//

#include <iostream>
#include <utility>

#include "player.h"

namespace traffic_racer
{

player::player(sf::RenderWindow& window, const std::string& name_texture)
    : car(window, name_texture)
    , mp_texture_loader(resource_loader::get_instance())
{
    m_position = DEFAULT_PLAYER_POSITION;
    m_speed = 250.f;
}

void player::update(sf::Event* event)
{
    if (!event) { return; }

    switch (event->type) {
        case sf::Event::KeyPressed:
            switch (event->key.code) {
                case sf::Keyboard::Left:
                    m_shift_position.x = -1.f;
                    break;
                case sf::Keyboard::Right:
                    m_shift_position.x = 1.f;
                    break;
            }
            break;
        case sf::Event::KeyReleased:
            switch (event->key.code) {
                case sf::Keyboard::Left:
                case sf::Keyboard::Right:
                    m_shift_position.x = 0.f;
                    break;
            }
    }
}

void player::move()
{
    float delta = m_clock.restart().asSeconds();
    if (delta >= 0.1f) { return; }
    m_position += m_shift_position * m_speed * delta;

    if (m_position.x > 600.f) { m_position.x = 600.f; }
    else if (m_position.x < 180.f) { m_position.x = 180.f; }

//    if (m_position.y < 20.f) { m_position.y = 20.f; }
//    else if (m_position.y > 450.f) { m_position.y = 450.f; }
}

} // namespace traffic_racer