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
{
    m_position = DEFAULT_PLAYER_POSITION;
}

void player::update(sf::Event* event)
{
    if (!event) { return; }

    switch (event->type) {
        case sf::Event::KeyPressed:
            std::cout << event->key.code << std::endl;
            switch (event->key.code) {
                case sf::Keyboard::Up:
                    m_shift_position.y = -1.f;
                    break;
                case sf::Keyboard::Down:
                    m_shift_position.y = 1.f;
                    break;
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
                case sf::Keyboard::Up:
                case sf::Keyboard::Down:
                    m_shift_position.y = 0.f;
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::Right:
                    m_shift_position.x = 0.f;
                    break;
            }
    }
}

void player::draw()
{
    move();

    sf::Texture* car_texture = mp_texture_loader->get("car");
    car_texture->setSmooth(true);

    sf::Sprite car;
    car.setScale({0.5f, 0.5f});
    car.setPosition(m_position);
    car.setTexture(*car_texture);

    m_window.draw(car);
}

void player::move()
{
    float delta = m_clock.restart().asSeconds();
    if (delta >= 0.1f) { return; }
    m_position += m_shift_position * 250.f * delta;

    if (m_position.x > 575.f) { m_position.x = 575.f; }
    else if (m_position.x < 140.f) { m_position.x = 140.f; }

    if (m_position.y < 20.f) { m_position.y = 20.f; }
    else if (m_position.y > 450.f) { m_position.y = 450.f; }
}

} // namespace traffic_racer