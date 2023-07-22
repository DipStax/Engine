#ifndef ENG_REND_IDRAWABLE_HPP
#define ENG_REND_IDRAWABLE_HPP

#include "Engine/Rendering/Texture.hpp"

namespace eng
{
    class RenderTarget;

    class IDrawable
    {
        protected:
            friend class RenderTarget;

            virtual void draw(RenderTarget &_target, const Texture *_txtr) const = 0;
    };
}

#endif