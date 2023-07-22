#ifndef ENG_REND_RENDERTEXTURE_HPP
#define ENG_REND_RENDERTEXTURE_HPP

#include "Engine/Rendering/RenderTarget.hpp"

namespace eng
{
    class RenderTexture : public RenderTarget
    {
        public:
            RenderTexture() = default;
            ~RenderTexture() = default;

            void create(uint32_t _x, uint32_t _y);

            [[nodiscard]] Texture &&getTexture() const;
            [[nodiscard]] Point2<uint32_t> getSize() const;

        private:
            Point2<uint32_t> m_size;
    };
}

#endif