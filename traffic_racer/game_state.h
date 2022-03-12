//
// Created by Кирилл Галимзянов on 10.03.2022.
//

#ifndef TRAFFICRACER_GAME_STATE_H
#define TRAFFICRACER_GAME_STATE_H

#include "state.h"
#include "state_machine.h"
#include "resource_loader.h"
#include "player.h"

namespace traffic_racer
{

class game_state final : public state
{
    const float DEFAULT_CARS_X_POSITION[4] = {
        175.f, 290.f, 425.f, 540.f
    };

public:
    enum LEVEL {
        EASY,
        MEDIUM,
        HARD
    };

    game_state(state_machine& machine, sf::RenderWindow& window, bool replace = true);

    void pause() override;
    void resume() override;

    void update() override;
    void draw() override;

    void set_level(const std::string& level);

protected:
    void load_resources_();
    void prev_generate_cars_();

    void remove_cars_off_map_();
    void add_cars_();

    std::shared_ptr<car> make_random_car_();

private:
    LEVEL m_level;

    player m_player;
    std::vector<std::shared_ptr<car>> m_cars;

    size_t m_count_cars;

    resource_loader* mp_resource_loader;

    std::pair<std::string, std::string> m_background_texture_path =
        {"../bin/img/background_game.png", "background"};

    std::vector<std::pair<std::string, std::string>> m_car_texture_paths = {
        {"../bin/img/cars/Ambulance.png", "ambulance"},
        {"../bin/img/cars/Audi.png", "audi"},
        {"../bin/img/cars/Black_viper.png", "black_viper"},
        {"../bin/img/cars/Car.png", "car"},
        {"../bin/img/cars/Mini_truck.png", "mini_truck"},
        {"../bin/img/cars/Mini_van.png", "mini_van"},
        {"../bin/img/cars/Police.png", "police"},
        {"../bin/img/cars/taxi.png", "taxi"},
        {"../bin/img/cars/truck.png", "truck"},
    };
    std::vector<std::pair<std::string, std::string>> m_reversed_car_texture_paths = {
        {"../bin/img/cars/r_Ambulance.png", "r_ambulance"},
        {"../bin/img/cars/r_Audi.png", "r_audi"},
        {"../bin/img/cars/r_Black_viper.png", "r_black_viper"},
        {"../bin/img/cars/r_Car.png", "r_car"},
        {"../bin/img/cars/r_Mini_truck.png", "r_mini_truck"},
        {"../bin/img/cars/r_Mini_van.png", "r_mini_van"},
        {"../bin/img/cars/r_Police.png", "r_police"},
        {"../bin/img/cars/r_taxi.png", "r_taxi"},
        {"../bin/img/cars/r_truck.png", "r_truck"},
    };
};

} // namespace traffic_racer

#endif //TRAFFICRACER_GAME_STATE_H
