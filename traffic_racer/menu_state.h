//
// Created by Кирилл Галимзянов on 05.03.2022.
//

#ifndef TRAFFICRACER_MENU_STATE_H
#define TRAFFICRACER_MENU_STATE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "state.h"

namespace sf
{
class RenderWindow;
} // namespace sf

namespace traffic_racer
{

class menu_state final : public state
{
public:
    menu_state(state_machine& machine, sf::RenderWindow& window, bool replace = true);

    void pause() override;
    void resume() override;

    void update() override;
    void draw() override;

private:
    sf::Texture m_background_texture;
    sf::Sprite m_background;

    std::string m_texture_path;
};

} // namespace traffic_racer

#endif //TRAFFICRACER_MENU_STATE_H
