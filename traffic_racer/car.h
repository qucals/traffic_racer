//
// Created by Кирилл Галимзянов on 11.03.2022.
//

#ifndef TRAFFICRACER_CAR_H
#define TRAFFICRACER_CAR_H

#include "entity.h"
#include "resource_loader.h"

namespace traffic_racer
{

class car : public entity
{
public:
    car(sf::RenderWindow& window, const std::string& name_texture, bool reverse = false);

    void update(sf::Event*) override;
    void draw() override;

    virtual void move();

    [[nodiscard]] const sf::Vector2f& get_position() const;
    void set_position(const sf::Vector2f& position);

    [[nodiscard]] const sf::Vector2f& get_shift_position() const;
    void set_shift_position(const sf::Vector2f& shift_position);

    [[nodiscard]] float get_speed() const;
    void set_speed(float speed);

    

protected:
    std::string m_name_texture;
    resource_loader* mp_resource_loader;

    sf::Sprite m_sprite;

    sf::Vector2f m_position;
    sf::Vector2f m_shift_position;
    sf::Clock m_clock;

    float m_speed;
};

} // namespace traffic_racer

#endif //TRAFFICRACER_CAR_H
