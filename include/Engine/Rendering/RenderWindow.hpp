#ifndef ENG_REND_RENDERWINDOW_HPP
#define ENG_REND_RENDERWINDOW_HPP

#include "Engine/Rendering/RenderTarget.hpp"
#include "Engine/Window.hpp"

namespace eng
{
    class RenderWindow : public Window, public RenderTarget
    {
        public:
            RenderWindow(uint32_t _x, uint32_t _y, const std::string& _title);
            ~RenderWindow() = default;

            [[nodiscard]] Point2<uint32_t> getSize() const;

            void setCamera(const Camera& _cam);

            void display();

        protected:
            void render(HDC _draw) const;

        private:
            Camera m_cam;
    };
}

#endif