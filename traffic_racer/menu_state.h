//
// Created by Кирилл Галимзянов on 05.03.2022.
//

#ifndef TRAFFICRACER_MENU_STATE_H
#define TRAFFICRACER_MENU_STATE_H

#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "state.h"

namespace sf
{
class RenderWindow;
} // namespace sf

namespace traffic_racer
{

class menu_state final : public state
{
    struct section
    {
        sf::Font font;
        sf::Text text;
        bool is_selected;
        std::function<void(menu_state&)> action;

        explicit section(const std::string& str, std::pair<int, int> position,
                         std::function<void(menu_state&)> action, bool is_selected = false,
                         size_t character_size = 24)
            : action(std::move(action))
            , is_selected(is_selected)
        {
            if (!font.loadFromFile("../bin/fonts/fira_code.ttf")) {
                throw std::runtime_error("Could not load font from file!");
            }

            text.setFont(font);
            text.setCharacterSize(character_size);
            text.setString(str);
            text.setPosition(position.first, position.second);

            set_selected(is_selected);
        }

        ~section() { std::cout << "remove section" << std::endl; }

        void set_selected(bool is_selected_)
        {
            text.setFillColor(is_selected_ ? sf::Color::Red : sf::Color::Black);
            text.setStyle(is_selected_ ? sf::Text::Bold : sf::Text::Regular);

            is_selected = is_selected_;
        }
    };

public:
    menu_state(state_machine& machine, sf::RenderWindow& window, bool replace = true);

    void pause() override;
    void resume() override;

    void update() override;
    void draw() override;

    void change_active_section(sf::Event::KeyEvent& key_event);
    std::size_t get_index_selected_section();

    inline static void play(menu_state& menu_state);

private:
    const std::vector<std::string> m_str_sections = {"Начать", "Выйти"};

    std::vector<section> m_sections;
};

void menu_state::play(menu_state& menu_state)
{}

} // namespace traffic_racer

#endif //TRAFFICRACER_MENU_STATE_H
