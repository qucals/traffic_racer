//
// Created by Кирилл Галимзянов on 05.03.2022.
//

#include "state_machine.h"

namespace traffic_racer
{

state_machine::state_machine()
    : m_resume{false}
    , m_running{false}
{
    std::cout << "state_machine init" << std::endl;
}

void state_machine::run(std::unique_ptr<state> state)
{
    m_running = true;
    m_states.push(std::move(state));
}

void state_machine::next_state()
{
    if (m_resume) {
        if (!m_states.empty()) { m_states.pop(); }
        if (!m_states.empty()) { m_states.top()->resume(); }

        m_resume = false;
    }

    if (!m_states.empty()) {
        auto temp = m_states.top()->next();

        if (temp != nullptr) {
            if (temp->is_replacing()) { m_states.pop(); }
            else { m_states.top()->pause(); }

            m_states.push(std::move(temp));
        }
    }
}

void state_machine::last_state()
{
    m_resume = true;
}

void state_machine::update()
{
    m_states.top()->update();
}

void state_machine::draw()
{
    m_states.top()->draw();
}

bool state_machine::running() const
{
    return m_running;
}

void state_machine::quit()
{
    m_running = false;
}

} // namespace traffic_racer