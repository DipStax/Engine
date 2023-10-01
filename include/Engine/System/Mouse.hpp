#pragma once

#include <windows.h>

#include "Tool/Export.hpp"
#include "Engine/Maths/Point2.hpp"

namespace eng
{
    class PROJECT_API Mouse
    {
        public:
            enum State {
                Press,
                Neutral,
                Release,
                DoubleClick
            };

            enum Button {
                Right,
                Left,
                Middle,
                X1,
                X2,
                Other
            };

            static eng::Point2<uint32_t> Position();
    };

    namespace priv
    {
        Mouse::Button mouseButtonConvert(uint64_t _key);
    }
}