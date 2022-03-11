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
public:
    explicit player(sf::RenderWindow& window);

    void update() override;
    void draw() override;
};

} // namespace traffic_racer

#endif //TRAFFICRACER_PLAYER_H
