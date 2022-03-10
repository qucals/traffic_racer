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
    , m_is_selecting_level{false}
{
    if (!DEFAULT_FONT.loadFromFile("../bin/fonts/fira_code.ttf")) {
        throw std::runtime_error("Could not load font from file!");
    }

    for (auto& str: m_str_main_sections) {
        m_main_sections.push_back(section{static_cast<std::string>(str), {}, [](menu_state&)
        {}, false});
    }
    m_main_sections[0].action = this->select_level;
    m_main_sections[0].set_selected(true);
    m_main_sections[1].action = [](menu_state& ms)
    { ms.m_machine.quit(); };

    for (auto& str: m_str_level_sections) {
        m_level_sections.push_back(section{static_cast<std::string>(str), {}, [](menu_state&)
        {}, false});
    }
    m_level_sections[m_level_sections.size() - 1].action = [](menu_state& ms)
    {
        ms.m_is_selecting_level = false;
    };
    m_level_sections[0].set_selected(true);

    text_centralization();

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
                        m_machine.quit();
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

    for (section& s: !m_is_selecting_level ? m_main_sections : m_level_sections) {
        m_window.draw(s.text);
    }

    m_window.display();
}

void menu_state::change_active_section(sf::Event::KeyEvent& key_event)
{
    std::vector<section>& sections = m_is_selecting_level ? m_level_sections : m_main_sections;
    size_t selected = get_index_selected_section(sections);

    switch (key_event.code) {
        case sf::Keyboard::Up:
            if (selected - 1 < 0) {
                sections[sections.size() - 1].set_selected(true);
            } else {
                sections[selected - 1].set_selected(true);
            }
            sections[selected].set_selected(false);
            break;
        case sf::Keyboard::Down:
            if (selected + 1 > sections.size() - 1) {
                sections[0].set_selected(true);
            } else {
                sections[selected + 1].set_selected(true);
            }
            sections[selected].set_selected(false);
            break;
        case sf::Keyboard::Enter:
            sections[selected].action(*this);
        default:
            break;
    }
}

std::size_t menu_state::get_index_selected_section(std::vector<section>& sections)
{
    for (std::size_t i = 0; i < sections.size(); i++) {
        if (sections[i].is_selected) { return i; }
    }
    return 0;
}

void menu_state::text_centralization()
{
    auto window_size = m_window.getSize();

    float increment = -50;
    for (section& s: m_main_sections) {
        sf::FloatRect rect = s.text.getLocalBounds();
        s.text.setOrigin(rect.left + rect.width / 2.0f,
                         rect.top + rect.height / 2.0f);
        s.text.setPosition({window_size.x / 2.0f, window_size.y / 2.0f + increment});
        increment += 50;
    }

    increment = -100;
    for (section& s: m_level_sections) {
        sf::FloatRect rect = s.text.getLocalBounds();
        s.text.setOrigin(rect.left + rect.width / 2.0f,
                         rect.top + rect.height / 2.0f);
        s.text.setPosition({window_size.x / 2.0f, window_size.y / 2.0f + increment});
        increment += 50;
    }
}

} // namespace traffic_racer