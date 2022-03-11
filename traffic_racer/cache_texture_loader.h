//
// Created by Кирилл Галимзянов on 10.03.2022.
//

#ifndef TRAFFICRACER_CACHE_TEXTURE_LOADER_H
#define TRAFFICRACER_CACHE_TEXTURE_LOADER_H

#include <map>
#include <string>

#include <SFML/Graphics/Texture.hpp>

namespace traffic_racer
{

class cache_texture_loader
{
public:
    cache_texture_loader(cache_texture_loader&) = delete;
    void operator=(const cache_texture_loader&) = delete;

    inline static cache_texture_loader* get_instance()
    {
        if (!cache_texture_loader::m_instance) { cache_texture_loader::m_instance = new cache_texture_loader(); }
        return cache_texture_loader::m_instance;
    }

    void load(const std::string& path, const std::string& name = "", bool replace = false)
    {
        if (!replace) {
            if (m_textures.find(name.empty() ? path : name) != std::end(m_textures)) {
                return;
            }
        }

        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::runtime_error("Could not load texture from file!");
        }

        m_textures[name.empty() ? path : name] = texture;
    }

    sf::Texture* get(const std::string& name)
    {
        if (m_textures.find(name) != std::end(m_textures)) {
            return &m_textures[name];
        }
        return nullptr;
    }

protected:
    cache_texture_loader() = default;

    inline static cache_texture_loader* m_instance;

private:
    std::map<std::string, sf::Texture> m_textures;
};

} // namespace traffic_racer

#endif //TRAFFICRACER_CACHE_TEXTURE_LOADER_H
