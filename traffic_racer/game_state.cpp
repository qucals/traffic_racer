//
// Created by Кирилл Галимзянов on 10.03.2022.
//

#include <random>

#include "game_state.h"

namespace traffic_racer
{

game_state::game_state(state_machine& machine, sf::RenderWindow& window, bool replace)
    : state(machine, window, replace)
    , mp_resource_loader(resource_loader::get_instance())
    , m_player(player(window, "car"))
    , m_level(LEVEL::EASY)
{
    load_resources_();
    generate_cars_();
}

void game_state::pause()
{

}

void game_state::resume()
{

}

void game_state::update()
{
    for (auto event = sf::Event{}; m_window.pollEvent(event);) {
        switch (event.type) {
            case sf::Event::Closed:
                m_machine.quit();
                break;
            case sf::Event::MouseButtonPressed:
                std::cout << sf::Mouse::getPosition(m_window).x << " "
                          << sf::Mouse::getPosition(m_window).y << std::endl;
                break;
            case sf::Event::KeyReleased:
            case sf::Event::KeyPressed:
                m_player.update(&event);
            default:
                break;
        }
    }

    for (auto& car : m_cars) {
        car->update(nullptr);
    }
}

void game_state::draw()
{
    m_window.clear();

    sf::Texture* background_texture = mp_resource_loader->get("background");
    sf::Sprite background;
    background.setTexture(*background_texture);

    m_window.draw(background);

    for (auto& car : m_cars) {
        car->draw();
    }

    m_player.draw();
    m_window.display();
}

void game_state::load_resources_()
{
    mp_resource_loader->load(m_background_texture_path.first, m_background_texture_path.second);

    for (auto& pr: m_car_texture_paths) {
        mp_resource_loader->load(pr.first, pr.second);
    }

    for (auto& pr: m_reversed_car_texture_paths) {
        mp_resource_loader->load(pr.first, pr.second);
    }
}

void game_state::generate_cars_()
{
    for (size_t i = 0; i < 5; i++) {
        int index = rand() % m_car_texture_paths.size();
        bool reverse = static_cast<bool>(rand() % 2);

        if (m_car_texture_paths[index].second == "car") {
            index++;
        }

        std::shared_ptr<car> pc = std::make_shared<car>(
            m_window,
            reverse ? m_reversed_car_texture_paths[index].second : m_car_texture_paths[index].second ,
            reverse);
        pc->set_position({DEFAULT_CARS_X_POSITION[(rand() % 4)], 100.f});
        pc->set_shift_position({0.f, -1.f});
        pc->set_speed(static_cast<float>(rand() % 50 + 5));

        if (reverse) { pc->set_speed(-1.f * pc->get_speed()); }

        m_cars.push_back(pc);
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