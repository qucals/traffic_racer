//
// Created by Кирилл Галимзянов on 10.03.2022.
//

#include "game_state.h"

namespace traffic_racer
{

game_state::game_state(state_machine& machine, sf::RenderWindow& window, bool replace)
    : state(machine, window, replace)
    , mp_texture_loader(cache_texture_loader::get_instance())
    , m_player(player(window))
    , m_level(LEVEL::EASY)
{
    load_texture_();
}

void game_state::pause()
{

}

void game_state::resume()
{

}

void game_state::update()
{

}

void game_state::draw()
{
    m_window.clear();

    sf::Texture* background_texture = mp_texture_loader->get("background");
    sf::Sprite background;
    background.setTexture(*background_texture);

    m_window.draw(background);

    m_window.display();
}

void game_state::load_texture_()
{
    for (auto& pr: m_texture_paths) {
        mp_texture_loader->load(pr.first, pr.second);
    }
}

void game_state::set_level(const std::string& level)
{
    if (level == "Easy") {
        m_level = LEVEL::EASY;
    } else if (level == "Medium") {
        m_level = LEVEL::MEDIUM;
    } else {
        m_level = LEVEL::HARD;
    }
}

} // namespace traffic_racer