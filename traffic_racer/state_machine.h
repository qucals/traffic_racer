//
// Created by Кирилл Галимзянов on 05.03.2022.
//

#ifndef TRAFFICRACER_STATE_MACHINE_H
#define TRAFFICRACER_STATE_MACHINE_H

#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>

#include "state.h"

namespace sf
{
class RenderWindow;
} // namespace sf

namespace traffic_racer
{

class state_machine
{
public:
    state_machine();

    void run(std::unique_ptr<state> st);

    void next_state();
    void last_state();

    void update();
    void draw();

    [[nodiscard]] bool running() const;
    void quit();

    template<typename T>
    static std::unique_ptr<T> build(state_machine &machine, sf::RenderWindow &window, bool replace = true);

private:
    std::stack<std::unique_ptr<state>> m_states;

    bool m_resume;
    bool m_running;
};

template<typename T>
std::unique_ptr<T> state_machine::build(state_machine &machine, sf::RenderWindow &window, bool replace)
{
    auto new_state = std::unique_ptr<T>{nullptr};

    try {
        new_state = std::make_unique<T>(machine, window, replace);
    } catch (std::runtime_error &ex) {
        std::cout << "Creation of new state was unsuccessful." << std::endl;
        std::cout << ex.what() << std::endl;
    }

    return new_state;
}

} // namespace traffic_racer

#endif //TRAFFICRACER_STATE_MACHINE_H
