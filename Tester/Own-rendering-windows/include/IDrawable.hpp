#pragma once

#include "Image.hpp"

namespace tester
{
    class RenderTarget;

    class IDrawable
    {
        protected:
            friend class RenderTarget;

            virtual void draw(RenderTarget &_target, Image *_img) const = 0;
    };
}