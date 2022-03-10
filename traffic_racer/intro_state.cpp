//
// Created by Кирилл Галимзянов on 05.03.2022.
//

#include <iostream>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "state_machine.h"
#include "intro_state.h"
#include "menu_state.h"

namespace traffic_racer
{

intro_state::intro_state(state_machine &machine, sf::RenderWindow &window, bool replace)
    : state{machine, window, replace}
    , m_alpha{0, 0, 0, 255}
    , m_texture_path{"../bin/img/intro.png"}
    {
    if (!m_background_texture.loadFromFile(m_texture_path)) {
        throw std::runtime_error{"Was unable to load image " + m_texture_path};
    }

    m_background.setTexture(m_background_texture, true);

    m_fader.setFillColor(m_alpha);
    m_fader.setSize(static_cast<sf::Vector2f>(m_background_texture.getSize()));

    std::cout << "intro_state init" << std::endl;
}

void traffic_racer::intro_state::pause()
{
    std::cout << "intro_state pause" << std::endl;
}

void traffic_racer::intro_state::resume()
{
    std::cout << "intro_state resume" << std::endl;
}

void traffic_racer::intro_state::update()
{
    for (auto event = sf::Event{}; m_window.pollEvent(event);) {
        switch (event.type) {
            case sf::Event::Closed:
                m_machine.quit();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Space:
                        m_next = state_machine::build<menu_state>(m_machine, m_window, true);
                        break;
                    case sf::Keyboard::Escape:
                        m_machine.quit();
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    if (m_alpha.a != 0) { m_alpha.a--; }
    m_fader.setFillColor(m_alpha);
}

void traffic_racer::intro_state::draw()
{
    m_window.clear();
    m_window.draw(m_background);

    if (m_alpha.a != 0) {
        m_window.draw(m_fader);
    }

    m_window.display();
}

} // namespace traffic_racer