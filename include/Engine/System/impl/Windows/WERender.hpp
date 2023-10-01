#pragma once

#include "Engine/System/impl/Windows/EventPack.hpp"
#include "Engine/System/impl/Interface/IWERender.hpp"

#include "Tool/Export.hpp"

namespace eng::impl::win
{
    class PROJECT_API WERender : public IWERender<WERender>
    {
        protected:
            [[nodiscard]] bool handle(const EventPack &_ep);

            void onDraw(Event _event);

            virtual void render(HDC _hdc) = 0;

        private:
            bool handleEvent(const EventPack &_ep);

            bool drawEvent(const EventPack &_ep);
    };
}