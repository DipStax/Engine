#pragma once

#include <functional>
#include <windows.h>
#include <string>

#include "Engine/Point2.hpp"
#include "Engine/Color.hpp"

#define EXT(_path) _path.substr(_path.rfind(".") + 1)

namespace tester
{
    class Image
    {
        public:
            Image() = default;
            ~Image();

            void load(const std::string &_path);

            [[nodiscard]] Point2<uint32_t> getSize() const;
            [[nodiscard]] Color getPixel(const Point2<uint32_t> &_pos) const;

        private:
            friend class RenderTarget;

            void facBmp(const std::string &_path);

            HBITMAP m_bmp;
            std::vector<uint8_t> m_pxl;
            Point2<uint32_t> m_size = { 0, 0 };
    };
}