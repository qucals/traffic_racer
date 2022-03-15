//
// Created by Кирилл Галимзянов on 10.03.2022.
//

#include "game_state.h"

namespace traffic_racer
{

game_state::game_state(state_machine& machine, sf::RenderWindow& window, bool replace)
    : state(machine, window, replace)
    , mp_resource_loader(resource_loader::get_instance())
    , m_count_cars(5)
{
    load_resources_();

    m_player = std::make_shared<player>(window, "car");
    m_background_sprite = sf::Sprite(*mp_resource_loader->get("background"));

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
                m_player->update(&event);
            default:
                break;
        }
    }

    for (auto& car: m_cars) {
        car->update(nullptr);
    }
}

void game_state::draw()
{
    remove_cars_off_map_();
    generate_cars_();

    m_window.clear();
    m_window.draw(m_background_sprite);

    for (auto& car: m_cars) {
        car->draw();
    }

    m_player->draw();
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
    std::uniform_int_distribution<int> distribution(0, m_count_cars - m_cars.size());
    for (size_t i = 0; i < distribution(m_generator); i++) {
        m_cars.push_back(make_random_car_());
    }
}

void game_state::remove_cars_off_map_()
{
    auto new_end = std::remove_if(std::begin(m_cars), std::end(m_cars), [](auto ptr)
    {
        auto pos = ptr->get_position();
        return pos.y <= -140.f || pos.y >= 600.f;
    });

    m_cars.erase(new_end, std::end(m_cars));
}

void game_state::set_level(const std::string& level)
{
    if (level == "Easy") {
        m_count_cars = 5;
    } else if (level == "Medium") {
        m_count_cars = 8;
    } else {
        m_count_cars = 10;
    }
}

std::shared_ptr<car> game_state::make_random_car_()
{
    std::uniform_int_distribution<int> index_distribution(0, m_car_texture_paths.size()-1);
    std::uniform_int_distribution<int> reverse_distribution(0, 1);
    std::uniform_int_distribution<float> speed_distribution(5.f, 100.f);

    int index = index_distribution(m_generator);
    bool reverse = static_cast<bool>(reverse_distribution(m_generator));

    if (m_car_texture_paths[index].second == "car") {
        index++;
    }

    std::shared_ptr<car> pc = std::make_shared<car>(
        m_window,
        reverse ? m_reversed_car_texture_paths[index].second : m_car_texture_paths[index].second,
        reverse);
    pc->set_shift_position({0.f,1.f});
    pc->set_speed(speed_distribution(m_generator));

    if (reverse) {
        pc->set_speed(-1.f * pc->get_speed());
        pc->set_position({DEFAULT_CARS_X_POSITION[reverse_distribution(m_generator)], -130.f});
        pc->set_speed(pc->get_speed() + m_player->get_speed());
    } else {
        pc->set_speed(abs(pc->get_speed() - m_player->get_speed()));
        pc->set_position({DEFAULT_CARS_X_POSITION[reverse_distribution(m_generator) + 2], -130.f});
    }

    return pc;
}

bool game_state::is_player_collided_with_car()
{


    return false;
}

} // namespace traffic_racer