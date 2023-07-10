#ifndef TESTER_COLOR_HPP
#define TESTER_COLOR_HPP

#define CLR(_clr) (static_cast<uint32_t>(_clr.A) << 24) + (static_cast<uint32_t>(_clr.B) << 16) + (static_cast<uint32_t>(_clr.G) << 8) + _clr.R

namespace tester
{
    struct Color
    {
        uint8_t R;
        uint8_t G;
        uint8_t B;
        uint8_t A;
    };

}

#endif