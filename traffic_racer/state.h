//
// Created by Кирилл Галимзянов on 05.03.2022.
//

#ifndef TRAFFICRACER_STATE_H
#define TRAFFICRACER_STATE_H

#include <memory>

namespace sf
{
class RenderWindow;
} // namespace sf

namespace traffic_racer
{

class state_machine;

class state
{
public:
    state(state_machine &machine, sf::RenderWindow &window, bool replace = true);
    virtual ~state() = default;

    state(const state &) = delete;
    state &operator=(const state &) = delete;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void update() = 0;
    virtual void draw() = 0;

    std::unique_ptr<state> next();

    [[nodiscard]] bool is_replacing() const;

protected:
    sf::RenderWindow &m_window;
    state_machine &m_machine;

    bool m_replacing;
    std::unique_ptr<state> m_next;
};

}


#endif //TRAFFICRACER_STATE_H
