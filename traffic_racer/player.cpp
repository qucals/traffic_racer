//
// Created by Кирилл Галимзянов on 11.03.2022.
//

#include <iostream>
#include <utility>

#include "player.h"

namespace traffic_racer
{

player::player(sf::RenderWindow& window, std::string name_texture)
    : car{window, std::move(name_texture)}
    , mp_texture_loader(resource_loader::get_instance())
{
    m_position = DEFAULT_PLAYER_POSITION;
    m_speed = 250.f;
}

void player::update(sf::Event* event)
{
    if (!event) { return; }

    switch (event->type) {
        case sf::Event::KeyPressed:
            std::cout << event->key.code << std::endl;
            switch (event->key.code) {
                case sf::Keyboard::Up:
                    m_shift_position.y = -1.f;
                    break;
                case sf::Keyboard::Down:
                    m_shift_position.y = 1.f;
                    break;
                case sf::Keyboard::Left:
                    m_shift_position.x = -1.f;
                    break;
                case sf::Keyboard::Right:
                    m_shift_position.x = 1.f;
                    break;
            }
            break;
        case sf::Event::KeyReleased:
            switch (event->key.code) {
                case sf::Keyboard::Up:
                case sf::Keyboard::Down:
                    m_shift_position.y = 0.f;
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::Right:
                    m_shift_position.x = 0.f;
                    break;
            }
    }
}

void player::draw()
{
    move();

    sf::Texture* car_texture = mp_texture_loader->get(m_name_texture);
    car_texture->setSmooth(true);

    sf::Sprite car;
    car.setScale({0.5f, 0.5f});
    car.setPosition(car.getPosition().x + m_position.x,
                    car.getPosition().y + m_position.y);
    car.setTexture(*car_texture);

//    sf::FloatRect bounding_box = car.getGlobalBounds();
//    car.setOrigin({bounding_box.left / 2, bounding_box.top / 2});
//    car.setRotation(180);

//    sf::RectangleShape rectangle(sf::Vector2f(128, 128));
//    rectangle.setPosition({bounding_box.left, bounding_box.top});
//    rectangle.setFillColor(sf::Color{ 0, 0, 0, 125 });
//    rectangle.setOutlineColor(sf::Color::Red);
//    rectangle.setTexture(car_texture);

//    m_window.draw(rectangle);
    m_window.draw(car);
}

void player::move()
{
    float delta = m_clock.restart().asSeconds();
    if (delta >= 0.1f) { return; }
    m_position += m_shift_position * m_speed * delta;

    if (m_position.x > 575.f) { m_position.x = 575.f; }
    else if (m_position.x < 140.f) { m_position.x = 140.f; }

    if (m_position.y < 20.f) { m_position.y = 20.f; }
    else if (m_position.y > 450.f) { m_position.y = 450.f; }
}

} // namespace traffic_racer