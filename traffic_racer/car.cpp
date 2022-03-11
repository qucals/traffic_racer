//
// Created by Кирилл Галимзянов on 11.03.2022.
//

#include "car.h"

namespace traffic_racer
{

car::car(sf::RenderWindow& window)
    : entity{window}
    , mp_texture_loader(cache_texture_loader::get_instance())
{
}

void car::update(sf::Event* event)
{

}

void car::draw()
{

}

} // namespace traffic_racer