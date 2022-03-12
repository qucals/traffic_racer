#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-default-arguments"
//
// Created by Кирилл Галимзянов on 10.03.2022.
//

#ifndef TRAFFICRACER_ENTITY_H
#define TRAFFICRACER_ENTITY_H

#include <SFML/Graphics.hpp>

namespace traffic_racer
{
class entity
{
public:
    explicit entity(sf::RenderWindow& window)
        : m_window{window}
    {}

    virtual ~entity() = default;

    virtual void update(sf::Event*) = 0;
    virtual void draw() = 0;

protected:
    sf::RenderWindow& m_window;
};

} // namespace traffic_racer

#endif //TRAFFICRACER_ENTITY_H

#pragma clang diagnostic pop