#pragma once

#include "PreProcessing.hpp"

namespace eng::ui
{
    template<class ...Ts>
    class IAcceptEvent
    {
        protected:
            template<class T>
            requires ContainIn<T, Ts...>;
            virtual void handleEvent(const T &_event) = 0;
    };
}