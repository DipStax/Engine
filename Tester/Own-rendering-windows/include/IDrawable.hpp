#pragma once

namespace tester
{
    class RenderWindow;

    class IDrawable
    {
        protected:
            friend RenderWindow;

            virtual bool draw(RenderWindow &_win) const = 0;
    };
}