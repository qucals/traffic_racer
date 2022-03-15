//
// Created by Кирилл Галимзянов on 11.03.2022.
//

#include <iostream>
#include <utility>

#include "car.h"

namespace traffic_racer
{

car::car(sf::RenderWindow& window, const std::string& name_texture, bool reverse)
    : entity{window}
    , m_name_texture{name_texture}
    , mp_resource_loader(resource_loader::get_instance())
    , m_sprite(*mp_resource_loader->get(m_name_texture))
    , m_speed(0)
{
    m_sprite.setScale({0.5f, 0.5f});
}

void car::update(sf::Event*)
{
}

void car::draw()
{
    move();

#ifdef SHOW_CAR_BOUNDS
    auto b = get_bounds();
    sf::RectangleShape rect({b.width, b.height});
    rect.setPosition(m_position.x,m_position.y);
    rect.setFillColor(sf::Color::White);
    m_window.draw(rect);
#endif // SHOW_CAR_BOUNDS

    m_sprite.setPosition(m_position.x,m_position.y);
    m_window.draw(m_sprite);
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

sf::FloatRect car::get_bounds() const
{
    return m_sprite.getGlobalBounds();
}

} // namespace traffic_racer