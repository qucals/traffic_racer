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
                if (event.key.code == sf::Keyboard::Escape) {
                    m_machine.last_state();
                } else {
                    m_player->update(&event);
                }
                break;
            default:
                break;
        }
    }

    for (auto& car: m_cars) {
        car->update(nullptr);
    }

#ifndef DISABLE_COLLISION
    if (is_player_collided_with_car()) {
        m_machine.last_state();
    }
#endif // DISABLE_COLLISION
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
    auto new_end = std::remove_if(std::begin(m_cars), std::end(m_cars), [this](auto ptr)
    {
        auto pos = ptr->get_position();
        return pos.y <= DEFAULT_TOP_BREAK_POSITION || pos.y >= DEFAULT_BOTTOM_BREAK_POSITION;
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
    std::uniform_int_distribution<int> reverse_distribution(0, 1);

    int index_texture_car = get_random_index_texture_car_();
    bool reverse = static_cast<bool>(reverse_distribution(m_generator));

    std::shared_ptr<car> pc = std::make_shared<car>(
        m_window,
        reverse ? m_reversed_car_texture_paths[index_texture_car].second
                : m_car_texture_paths[index_texture_car].second,
        reverse);
    pc->set_shift_position({0.f, 1.f});

    int start_shift_position = reverse ? 0 : 2;
    sf::Vector2f position{DEFAULT_CARS_X_POSITION[reverse_distribution(m_generator) + start_shift_position], -130.f};
    pc->set_position(position);

    std::uniform_int_distribution<float> speed_distribution(40.f, get_limit_of_speed_(position.x, reverse));
    pc->set_speed(speed_distribution(m_generator));

    if (reverse) {
        pc->set_speed(-1.f * pc->get_speed() + m_player->get_speed());
    } else {
        pc->set_speed(abs(pc->get_speed() - m_player->get_speed()));
    }

    return pc;
}

int game_state::get_random_index_texture_car_()
{
    std::uniform_int_distribution<int> index_distribution(0, m_car_texture_paths.size() - 1);
    int index = index_distribution(m_generator);
    if (m_car_texture_paths[index].second == "car") { index++; }
    return index;
}

float game_state::get_limit_of_speed_(float x_road, bool reverse) const
{
    std::shared_ptr<car> first_car = get_first_car_in_road_(x_road, reverse);

    if (!first_car) {
        return 100.f;
    }

    // x – другая машина
    float x_pos = first_car->get_position().y;
    float x_speed = first_car->get_speed();
    // Начало движения новой машины
    float start_pos = reverse ? DEFAULT_BOTTOM_BREAK_POSITION : DEFAULT_TOP_BREAK_POSITION;
    // Конец завершения движения машин
    float end_pos = !reverse ? DEFAULT_BOTTOM_BREAK_POSITION : DEFAULT_TOP_BREAK_POSITION;

    float y_speed = ((start_pos - x_pos) * x_speed) / (end_pos - x_pos) + x_speed;

    return y_speed;
}

std::shared_ptr<car> game_state::get_first_car_in_road_(float x_road, bool reverse) const
{
    std::shared_ptr<car> min = nullptr;

    for (const auto& car: m_cars) {
        if (car->get_position().x != x_road) { continue; }

        if (min) {
            if (reverse && min->get_position().y > car->get_position().y) {
                min = car;
            } else if (!reverse && min->get_position().y < car->get_position().y) {
                min = car;
            }
        } else {
            min = car;
        }
    }

    return min;
}

bool game_state::is_player_collided_with_car()
{
    auto player_bounds = m_player->get_bounds();

    if (player_bounds.top == 0 && player_bounds.left == 0) { return false; }

    return std::any_of(std::begin(m_cars), std::end(m_cars),
                       [&player_bounds](const auto& car)
                       {
                           return car->get_bounds().intersects(player_bounds);
                       });
}


} // namespace traffic_racer