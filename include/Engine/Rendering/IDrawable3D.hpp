#ifndef ENG_REND_IDRAWABLE3D_HPP
#define ENG_REND_IDRAWABLE3D_HPP

#include "Engine/Rendering/Texture.hpp"

namespace eng
{
    class RenderTarget3D;

    class IDrawable3D
    {
        protected:
            friend class RenderTarget;

            virtual void draw(RenderTarget &_target, const Texture *_txtr) const = 0;
    };
}

#endif