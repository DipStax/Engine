#pragma once

namespace tester
{
    class RenderTarget;
 
    class IDrawable
    {
        protected:
            friend class RenderTarget;

            virtual void draw(RenderTarget &_win) const = 0;
    };
}