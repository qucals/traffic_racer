//
// Created by Кирилл Галимзянов on 05.03.2022.
//

#include "state.h"

namespace traffic_racer
{

state::state(state_machine &machine, sf::RenderWindow &window, const bool replace)
    : m_machine{machine}
    , m_window{window}
    , m_replacing{replace}
{}

std::unique_ptr<state> state::next()
{
    return std::move(m_next);
}

bool state::is_replacing() const
{
    return m_replacing;
}

} // namespace traffic_racer