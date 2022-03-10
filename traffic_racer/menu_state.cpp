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

menu_state::menu_state(state_machine& machine, sf::RenderWindow& window, bool replace)
    : state{machine, window, replace}
{
    auto window_size = window.getSize();

    auto center_x = int(window_size.x / 2);
    auto start_y = 50;

    m_sections.push_back(
        section{m_str_sections[0], {center_x, start_y}, this->play, true}
    );
    m_sections.push_back(
        section{m_str_sections[1], {center_x + 30, start_y}, [](menu_state& ms)
        {
            ms.m_machine.quit();
        }, false}
    );

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
                        change_active_section(event.key);
                        break;
                }
            default:
                break;
        }
    }
}

void menu_state::draw()
{
    m_window.clear(sf::Color::White);

    for (section& s: m_sections) {
        m_window.draw(s.text);
    }

    m_window.display();
}

void menu_state::change_active_section(sf::Event::KeyEvent& key_event)
{
    size_t selected = get_index_selected_section();

    switch (key_event.code) {
        case sf::Keyboard::Up:
            if (selected - 1 < 0) {
                m_sections[m_sections.size() - 1].set_selected(true);
            } else {
                m_sections[selected - 1].set_selected(true);
            }
            m_sections[selected].set_selected(false);
            break;
        case sf::Keyboard::Down:
            if (selected + 1 > m_sections.size() - 1) {
                m_sections[0].set_selected(true);
            } else {
                m_sections[selected + 1].set_selected(true);
            }
            m_sections[selected].set_selected(false);
            break;
        default:
            break;
    }
}

std::size_t menu_state::get_index_selected_section()
{
    for (std::size_t i = 0; i < m_sections.size(); i++) {
        if (m_sections[i].is_selected) { return i; }
    }
    return 0;
}

} // namespace traffic_racer