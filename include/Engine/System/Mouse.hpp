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
                Right = 0,
                Left = 1,
                Middle = 2,
                X1 = 4,
                X2 = 8,
                Other = 16
            };

            static eng::Point2<uint32_t> Position();
    };

    namespace priv
    {
        Mouse::Button mouseButtonConvert(uint64_t _key);
    }
}