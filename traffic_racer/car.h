//
// Created by Кирилл Галимзянов on 11.03.2022.
//

#ifndef TRAFFICRACER_CAR_H
#define TRAFFICRACER_CAR_H

#include "entity.h"
#include "cache_texture_loader.h"

namespace traffic_racer
{

class car : public entity
{
public:
    car(sf::RenderWindow& window);

    virtual void update(sf::Event* event) override;
    virtual void draw() override;

protected:
    cache_texture_loader* mp_texture_loader;

    sf::Vector2f m_position;
    sf::Vector2f m_shift_position;
};

} // namespace traffic_racer

#endif //TRAFFICRACER_CAR_H
