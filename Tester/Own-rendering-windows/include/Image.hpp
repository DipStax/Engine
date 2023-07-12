#pragma once

#include <functional>
#include <windows.h>
#include <string>

#include "Engine/Point2.hpp"

#define EXT(_path) _path.substr(_path.rfind(".") + 1)

namespace tester
{
    class Image
    {
        public:
            Image() = default;
            ~Image() = default;

            void load(const std::string &_path);

            [[nodiscard]] Point2<uint32_t> getSize() const;

        private:
            friend class RenderTarget;

            void facBmp(const std::string &_path);

            HBITMAP m_bmp;
    };
}