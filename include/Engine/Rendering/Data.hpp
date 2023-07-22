#ifndef ENG_RSC_DATA_HPP
#define ENG_RSC_DATA_HPP

#include <vector>

#include "Engine/Rendering/Model.hpp"

namespace eng
{
    struct Data
    {
        std::map<size_t, std::shared_ptr<Texture>> Texture;
        std::map<size_t, std::unique_ptr<Model>> Model;
    };
}

#endif