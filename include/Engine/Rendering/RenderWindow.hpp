#pragma once

#include "Engine/Event/Event.hpp"
#include "Engine/Event/EventPool.hpp"
#include "Engine/Rendering/RenderTarget.hpp"
#include "Engine/System/Window.hpp"

namespace eng
{
    using EPWindow = EventPool<Event::MouseButton, Event::Resize>;

    class PROJECT_API RenderWindow : public EPWindow, public Window, public RenderTarget
    {
        public:
            RenderWindow(ThreadPool &_tp, uint32_t _x, uint32_t _y, const std::string &_title);
            ~RenderWindow() = default;

            [[nodiscard]] Point2<uint32_t> getSize() const;

            void setCamera(const Camera& _cam);

            bool pollEvent(Event &_event);

            void display();

        protected:
            void render(HDC _draw) const;

            void onResize(Event _event) override;
            void onMouseButtonEvent(Event _event) override;

        private:
            Camera m_cam;
            Point2<uint32_t> m_size;

            ts::Queue<Event> m_event;
    };
}