#pragma once

#include "Engine/Event/EventPool.hpp"
#include "Engine/Rendering/Sprite.hpp"
#include "Engine/Rendering/RenderTexture.hpp"

namespace eng::ui
{
    class Object : public IDrawable, protected RenderTarget
    {
        public:
            Object();
            ~Object() = default;

        protected:
            void draw(RenderTarget &_target, const Texture *_txtr) const override;
    };
}