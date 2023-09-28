#pragma once

#include "Engine/Rendering/RenderTarget.hpp"
#include "Engine/System/Window.hpp"

namespace eng
{
    class PROJECT_API RenderWindow : public Window, public RenderTarget
    {
        public:
            RenderWindow(uint32_t _x, uint32_t _y, const std::string& _title);
            ~RenderWindow() = default;

            [[nodiscard]] Point2<uint32_t> getSize() const;

            void setCamera(const Camera& _cam);

            void display();

        protected:
            void render(HDC _draw) const;

            void onResize(const Event &_event) override;

        private:
            Camera m_cam;
            Point2<uint32_t> m_size;
    };
}