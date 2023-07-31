#include <iostream>

#include "Engine/Rendering/RenderTexture.hpp"

namespace eng
{
    void RenderTexture::create(uint32_t _x, uint32_t _y)
    {
        m_size = { _x, _y };
        RenderTarget::create(_x, _y);
    }

    Texture RenderTexture::getTexture() const
    {
        Texture txtr;

        txtr.load(getData(), m_size);
        return txtr;
    }

    Point2<uint32_t> RenderTexture::getSize() const
    {
        return m_size;
    }
}