#pragma once

#include "Engine/Rendering/Texture.hpp"

namespace eng
{
    class RenderTarget;

    class IDrawable3D
    {
        protected:
            friend class RenderTarget;

            virtual void draw(RenderTarget &_target, const Texture *_txtr) const = 0;
    };
}