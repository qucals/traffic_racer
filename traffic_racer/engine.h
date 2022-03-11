//
// Created by Кирилл Галимзянов on 05.03.2022.
//

#ifndef TRAFFICRACER_ENGINE_H
#define TRAFFICRACER_ENGINE_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "state_machine.h"

namespace traffic_racer
{

const sf::VideoMode WINDOW_SIZE{800, 600};
const std::string WINDOW_TITLE = "Traffic Racer";
const size_t FRAMERATE_LIMIT = 0;

class engine
{
public:
    void run();

private:
    sf::RenderWindow m_window;
    state_machine m_machine;
};

} // namespace traffic_racer

#endif //TRAFFICRACER_ENGINE_H
