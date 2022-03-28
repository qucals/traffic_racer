//
// Created by Кирилл Галимзянов on 05.03.2022.
//

#ifndef TRAFFICRACER_MENU_STATE_H
#define TRAFFICRACER_MENU_STATE_H

#include <utility>
#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "state.h"
#include "resource_loader.h"
#include "game_state.h"

namespace sf
{
class RenderWindow;
} // namespace sf

namespace traffic_racer
{

class menu_state final : public state
{
public:
    inline static sf::Font DEFAULT_FONT;

    struct section
    {
        sf::Text text;
        bool is_selected;
        std::function<void(menu_state&)> action;

        explicit section(const std::string& str, std::pair<int, int> position,
                         std::function<void(menu_state&)> action, bool is_selected = false,
                         size_t character_size = 24)
            : action(std::move(action))
            , is_selected(is_selected)
        {
            text.setFont(menu_state::DEFAULT_FONT);
            text.setCharacterSize(character_size);
            text.setString(str);
            text.setPosition(position.first, position.second);

            set_selected(is_selected);
        }

        void set_selected(bool is_selected_)
        {
            text.setFillColor(is_selected_ ? sf::Color::Magenta : sf::Color::Black);
            text.setStyle(is_selected_ ? sf::Text::Bold : sf::Text::Regular);

            is_selected = is_selected_;
        }
    };

    menu_state(state_machine& machine, sf::RenderWindow& window, bool replace = true);

    void pause() override;
    void resume() override;

    void update() override;
    void draw() override;

protected:
    void change_active_section_(sf::Event::KeyEvent& key_event);
    static std::size_t get_index_selected_section_(std::vector<section>& sections);

    inline static void select_level_(menu_state& menu_state);

    void text_centralization_();

private:
    const std::vector<std::string> m_str_main_sections = {"Start", "Quit"};
    std::vector<section> m_main_sections;

    const std::vector<std::string> m_str_level_sections{"Easy", "Medium", "Hard", "Back"};
    std::vector<section> m_level_sections;

    bool m_is_selecting_level;

    int m_score;
};

void menu_state::select_level_(menu_state& menu_state)
{
    menu_state.m_is_selecting_level = true;
}

} // namespace traffic_racer

#endif //TRAFFICRACER_MENU_STATE_H
