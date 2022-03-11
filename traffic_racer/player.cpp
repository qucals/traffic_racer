//
// Created by Кирилл Галимзянов on 11.03.2022.
//

#include <iostream>

#include "player.h"

namespace traffic_racer
{

player::player(sf::RenderWindow& window)
    : car{window}
    , mp_texture_loader(cache_texture_loader::get_instance())
    , m_position(DEFAULT_PLAYER_POSITION)
{
}

void player::update(sf::Event* event)
{
    if (!event) { return; }

    switch (event->type) {
        case sf::Event::KeyReleased:
        case sf::Event::KeyPressed:
            std::cout << event->key.code << std::endl;
            switch (event->key.code) {
                case sf::Keyboard::Up:
                    m_position.y -= 5.f;
                    break;
                case sf::Keyboard::Down:
                    m_position.y += 5.f;
                    break;
                case sf::Keyboard::Left:
                    m_position.x -= 5.f;
                    break;
                case sf::Keyboard::Right:
                    m_position.x += 5.f;
                    break;
            }
            break;
    }
}

void player::draw()
{
    sf::Texture* car_texture = mp_texture_loader->get("car");
    car_texture->setSmooth(true);

    sf::Sprite car;
    car.setScale({0.5f, 0.5f});
    car.setPosition(m_position);
    car.setTexture(*car_texture);

    m_window.draw(car);
}

const sf::Vector2f& player::get_position() const
{
    return m_position;
}

void player::set_position(const sf::Vector2f& position)
{
    m_position = position;
}

} // namespace traffic_racer