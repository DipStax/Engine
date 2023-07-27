#ifndef ENG_REND_RENDERWINDOW_HPP
#define ENG_REND_RENDERWINDOW_HPP

#include "Engine/Rendering/RenderTarget3D.hpp"
#include "Engine/Window.hpp"

namespace eng
{
    class RenderWindow : public Window, public RenderTarget, public RenderTarget3D
    {
        public:
            RenderWindow(uint32_t _x, uint32_t _y, const std::string& _title);
            ~RenderWindow() = default;

            [[nodiscard]] Point2<uint32_t> getSize() const;

            void draw(const IDrawable &_elem, const Texture *_txtr = nullptr);
            void draw(const IDrawable3D &_elem, const Texture *_txtr = nullptr);

            void clear(const Color& _clr = { 0, 0, 0, 255 });

            void display() const;

        protected:
            void render(HDC _draw) const;
    };
}

#endif