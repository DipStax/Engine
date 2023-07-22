#ifndef ENG_REND_IDRAWABLE3D_HPP
#define ENG_REND_IDRAWABLE3D_HPP

#include "Engine/Rendering/Texture.hpp"

namespace eng
{
    class RenderTarget3D;

    class IDrawable3D
    {
        protected:
            friend class RenderTarget3D;

            virtual void draw(RenderTarget3D &_target, const Texture *_txtr) const = 0;
    };
}

#endif