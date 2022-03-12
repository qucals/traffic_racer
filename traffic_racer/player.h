//
// Created by Кирилл Галимзянов on 11.03.2022.
//

#ifndef TRAFFICRACER_PLAYER_H
#define TRAFFICRACER_PLAYER_H

#include "car.h"
#include "cache_texture_loader.h"

namespace traffic_racer
{

class player final : public car
{
    inline static sf::Vector2f DEFAULT_PLAYER_POSITION = {425.f, 450.f};

public:
    explicit player(sf::RenderWindow& window);

    void update(sf::Event* event) override;
    void draw() override;

    void move() override;

protected:
    float m_speed;
    sf::Clock m_clock;

    cache_texture_loader* mp_texture_loader;
};

} // namespace traffic_racer

#endif //TRAFFICRACER_PLAYER_H
