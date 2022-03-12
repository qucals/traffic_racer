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
    car(sf::RenderWindow& window, bool reverse = false);

    void draw() override;
    virtual void move();

    [[nodiscard]] const sf::Vector2f& get_position() const;
    void set_position(const sf::Vector2f& position);

protected:
    cache_texture_loader* mp_texture_loader;

    sf::Vector2f m_position;
    sf::Vector2f m_shift_position;

    bool m_reverse;
};

} // namespace traffic_racer

#endif //TRAFFICRACER_CAR_H
