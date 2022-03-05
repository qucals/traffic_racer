//
// Created by Кирилл Галимзянов on 05.03.2022.
//

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "state_machine.h"
#include "menu_state.h"

namespace traffic_racer
{

menu_state::menu_state(state_machine &machine, sf::RenderWindow &window, bool replace)
    : state{machine, window, replace}
    , m_texture_path("../bin/img/menu.png")
{
    if (!m_background_texture.loadFromFile(m_texture_path)) {
        throw std::runtime_error("Was unable to load image " + m_texture_path);
    }

    m_background.setTexture(m_background_texture, true);

    std::cout << "menu_state init" << std::endl;
}

void menu_state::pause()
{
    std::cout << "menu_state pause" << std::endl;
}

void menu_state::resume()
{
    std::cout << "menu_state resume" << std::endl;
}

void menu_state::update()
{
    for (auto event = sf::Event{}; m_window.pollEvent(event);) {
        switch (event.type) {
            case sf::Event::Closed:
                m_machine.quit();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        m_machine.last_state();
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }
}

void menu_state::draw()
{
    m_window.clear();
    m_window.draw(m_background);
    m_window.display();
}
} // namespace traffic_racer