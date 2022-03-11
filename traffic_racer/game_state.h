//
// Created by Кирилл Галимзянов on 10.03.2022.
//

#ifndef TRAFFICRACER_GAME_STATE_H
#define TRAFFICRACER_GAME_STATE_H

#include "state.h"
#include "state_machine.h"
#include "cache_texture_loader.h"
#include "player.h"

namespace traffic_racer
{

class game_state final : public state
{

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
    void load_texture_();
    void generate_cars_();

private:
    LEVEL m_level;

    player m_player;
    std::vector<car> m_cars;

    cache_texture_loader* mp_texture_loader;
    std::vector<std::pair<std::string, std::string>> m_texture_paths = {
        {"../bin/img/background_game.png", "background"},
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
};

} // namespace traffic_racer

#endif //TRAFFICRACER_GAME_STATE_H
