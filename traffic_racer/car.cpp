//
// Created by Кирилл Галимзянов on 11.03.2022.
//

#include <iostream>
#include <utility>

#include "car.h"

namespace traffic_racer
{

car::car(sf::RenderWindow& window, std::string name_texture, bool reverse)
    : entity{window}
    , m_name_texture{std::move(name_texture)}
    , mp_texture_loader(resource_loader::get_instance())
    , m_reverse{reverse}
    , m_speed(0)
{
}

void car::update(sf::Event*)
{
}

void car::draw()
{
    move();

    sf::Texture* car_texture = mp_texture_loader->get(m_name_texture);
    car_texture->setSmooth(true);

    sf::Sprite car;
    car.setScale({0.5f, 0.5f});
    car.setPosition(m_position);
    car.setTexture(*car_texture);

    m_window.draw(car);
}
void car::move()
{
    float delta = m_clock.restart().asSeconds();
    if (delta >= 0.1f) { return; }
    m_position += m_shift_position * m_speed * delta;
}

const sf::Vector2f& car::get_position() const
{
    return m_position;
}

void car::set_position(const sf::Vector2f& position)
{
    m_position = position;
}

const sf::Vector2f& car::get_shift_position() const
{
    return m_shift_position;
}

void car::set_shift_position(const sf::Vector2f& shift_position)
{
    m_shift_position = shift_position;
}

float car::get_speed() const
{
    return m_speed;
}

void car::set_speed(float speed)
{
    m_speed = speed;
}

} // namespace traffic_racer