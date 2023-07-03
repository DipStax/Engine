#ifndef ENG_RSC_DATA_HPP
#define ENG_RSC_DATA_HPP

#include <vector>

#include <sfml/Graphics/Texture.hpp>
#include <sfml/Graphics/Font.hpp>

#include "Engine/Ressource/Model.hpp"

namespace eng
{
    struct Data
    {
        std::map<size_t, std::shared_ptr<sf::Texture>> Texture;
        std::map<size_t, std::shared_ptr<sf::Font>> Font;
        std::map<size_t, std::unique_ptr<Model>> Model;
    };
}

#endif