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

    virtual void move();

    [[nodiscard]] const sf::Vector2f& get_position() const;
    void set_position(const sf::Vector2f& position);

protected:
    sf::Vector2f m_position;
    sf::Vector2f m_shift_position;

    float m_speed;
    sf::Clock m_clock;

    cache_texture_loader* mp_texture_loader;
};

} // namespace traffic_racer

#endif //TRAFFICRACER_PLAYER_H
