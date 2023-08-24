#pragma once

#include <vector>

#include "Engine/Rendering/Model.hpp"

namespace eng
{
    struct PROJECT_API Data
    {
        std::map<size_t, std::shared_ptr<Texture>> Texture;
        std::map<size_t, std::shared_ptr<Model>> Model;
    };
}