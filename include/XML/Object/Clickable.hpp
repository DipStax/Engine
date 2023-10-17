#pragma once

#include "Engine/Event/Event.hpp"
#include "Engine/Event/EventPool.hpp"
#include "XML/UI/IAcceptEvent.hpp"

namespace eng::ui
{
    class Clickable : public IAcceptEvent<eng::Event::MouseButton>
    {
        protected:
            template<class ...Ts>
            requires ContainIn<eng::Event::MouseButton, Ts...>
            Clickable(eng::EventPool<Ts...> &_pe);

            template<class ...Ts>
            requires ContainIn<eng::Event::MouseButton, Ts...>
            ~Clickable(eng::EventPool<Ts...> &_pe);

            virtual void onClick(const eng::Event::MouseButton &_event) = 0;

        private:
            eng::Trigger<eng::Event::MouseButton>::sTask m_stask;
    };
}