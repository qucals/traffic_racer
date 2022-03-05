//
// Created by Кирилл Галимзянов on 05.03.2022.
//

#ifndef TRAFFICRACER_INTRO_STATE_H
#define TRAFFICRACER_INTRO_STATE_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "state.h"

namespace sf
{
class RenderWindow;
} // namespace sf

namespace traffic_racer
{

class state_machine;

class intro_state final : public state
{
public:
    intro_state(state_machine& machine, sf::RenderWindow& window, bool replace = true);

    void pause() override;
    void resume() override;

    void update() override;
    void draw() override;

private:
    sf::Texture m_background_texture;
    sf::Sprite m_background;
    sf::RectangleShape m_fader;
    sf::Color m_alpha;

    std::string m_texture_path;
};

} // namespace traffic_racer

#endif //TRAFFICRACER_INTRO_STATE_H
