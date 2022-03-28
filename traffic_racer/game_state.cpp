//
// Created by Кирилл Галимзянов on 10.03.2022.
//

#include "game_state.h"
#include "menu_state.h"

namespace traffic_racer
{

game_state::game_state(state_machine& machine, sf::RenderWindow& window, bool replace)
    : state(machine, window, replace)
    , mp_resource_loader(resource_loader::get_instance())
    , m_count_cars(5)
    , m_free_status_roads(4, true)
    , m_generator(time(nullptr))
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
#ifdef MOUSE_CLICK_SHOW_POSITION
                case sf::Event::MouseButtonPressed:
                    std::cout << sf::Mouse::getPosition(m_window).x << " "
                              << sf::Mouse::getPosition(m_window).y << std::endl;
                    break;
#endif // MOUSE_CLICK_SHOW_POSITION
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

    if (!m_score) {
        throw std::runtime_error("The address space for the score is not set!");
    }

    if (m_player->get_position().x < 420) {
        *m_score += 2;
    } else {
        *m_score += 1;
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

    draw_score_();

    m_window.display();
}

void game_state::draw_score_()
{
    sf::RectangleShape rectangle({80, 40});
    rectangle.setPosition({10, 10});

    sf::Text score_text(std::to_string(*m_score / 1000), menu_state::DEFAULT_FONT, 18);

    score_text.setFillColor(sf::Color::Black);
    score_text.setPosition(18, 19);

    m_window.draw(rectangle);
    m_window.draw(score_text);
}

void game_state::set_pointer_to_score(int* score)
{
    m_score = score;
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
    for (int i = 0; i < m_free_status_roads.size(); i++) {
        if (!m_free_status_roads[i]) {
            auto car = get_first_car_in_road_(DEFAULT_CARS_X_POSITION[i]);
            m_free_status_roads[i] = !car || car->get_position().y > (100.0f + car->get_bounds().width);
        }
    }

    int free_roads = std::count(std::begin(m_free_status_roads),
                                std::end(m_free_status_roads), true);

    std::uniform_int_distribution<int> distribution(0, m_count_cars - m_cars.size());

    for (size_t i = 0; i < distribution(m_generator) && i < free_roads; i++) {
        m_cars.push_back(make_random_car_());
    }
}

void game_state::remove_cars_off_map_()
{
    auto new_end = std::remove_if(std::begin(m_cars), std::end(m_cars), [this](auto ptr)
    {
        auto pos = ptr->get_position();
        return pos.y >= STOP_CAR_POSITION;
    });

    m_cars.erase(new_end, std::end(m_cars));
}

void game_state::set_level(const std::string& level)
{
    if (level == "Easy") {
        m_count_cars = 3;
    } else if (level == "Medium") {
        m_count_cars = 5;
    } else {
        m_count_cars = 7;
    }
}

std::shared_ptr<car> game_state::make_random_car_()
{
    std::vector<int> free_roads;
    for (int i = 0; i < m_free_status_roads.size(); i++) {
        if (m_free_status_roads[i]) { free_roads.push_back(i); }
    }

    std::uniform_int_distribution<int> road_distribution(0, free_roads.size() - 1);

    int index_texture_car = get_random_index_texture_car_();
    int id_road = free_roads[road_distribution(m_generator)];
    bool reverse = id_road < 2;

    std::shared_ptr<car> pc = std::make_shared<car>(
        m_window,
        reverse ? m_reversed_car_texture_paths[index_texture_car].second
                : m_car_texture_paths[index_texture_car].second,
        reverse);
    pc->set_shift_position({0.f, 1.f});


    sf::Vector2f position{DEFAULT_CARS_X_POSITION[id_road], -130.f};
    pc->set_position(position);

    float limit = get_limit_of_speed_(position.x);
    std::uniform_real_distribution<float> speed_distribution(125.f, limit);
    float speed = speed_distribution(m_generator);
    pc->set_speed(speed);

    m_free_status_roads[id_road] = false;

    return pc;
}

int game_state::get_random_index_texture_car_()
{
    std::uniform_int_distribution<int> index_distribution(0, m_car_texture_paths.size() - 1);
    int index = index_distribution(m_generator);
    if (m_car_texture_paths[index].second == "car") { index++; }
    return index;
}

float game_state::get_limit_of_speed_(float x_road) const
{
    std::shared_ptr<car> first_car = get_first_car_in_road_(x_road);

    if (!first_car) {
        return 250.f;
    }

    // x – другая машина
    float x_pos = first_car->get_position().y;
    float x_car_size = first_car->get_bounds().height;
    float x_speed = first_car->get_speed();

    float y_speed = (fabs((START_CAR_POSITION - x_pos + x_car_size)) * x_speed) /
        (STOP_CAR_POSITION + x_car_size - x_pos) + x_speed;

    if (y_speed > 500.f) { y_speed = 500.f; }

    return y_speed;
}

std::shared_ptr<car> game_state::get_first_car_in_road_(float x_road) const
{
    std::shared_ptr<car> min = nullptr;

    for (const auto& car: m_cars) {
        if (car->get_position().x != x_road) { continue; }

        if (min) {
            if (min->get_position().y > car->get_position().y) {
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