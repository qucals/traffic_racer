//
// Created by Кирилл Галимзянов on 05.03.2022.
//

#include "engine.h"
#include "menu_state.h"

namespace traffic_racer
{

void engine::run()
{
    m_window.create(WINDOW_SIZE, WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);
    m_window.setFramerateLimit(FRAMERATE_LIMIT);

    m_machine.run(state_machine::build<menu_state>(m_machine, m_window, true));

    while (m_machine.running()) {
        m_machine.next_state();
        m_machine.update();
        m_machine.draw();

    }
}

} // namespace traffic_racer
