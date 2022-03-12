//
// Created by Кирилл Галимзянов on 11.03.2022.
//

#include "car.h"

namespace traffic_racer
{

car::car(sf::RenderWindow& window, bool reverse)
    : entity{window}
    , mp_texture_loader(cache_texture_loader::get_instance())
    , m_reverse{reverse}
{
}

void car::draw()
{

}

void car::move()
{

}

const sf::Vector2f& car::get_position() const
{
    return m_position;
}

void car::set_position(const sf::Vector2f& position)
{
    m_position = position;
}

} // namespace traffic_racer