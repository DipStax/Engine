#pragma once

#include "Engine/Event/EventPool.hpp"
#include "Engine/Rendering/Sprite.hpp"
#include "Engine/Rendering/RenderTexture.hpp"

namespace eng::ui
{
    class BaseObject : public IDrawable, protected RenderTarget
    {
        public:
            BaseObject();
            ~BaseObject() = default;

        protected:
            void draw(RenderTarget &_target, const Texture *_txtr) const override;
    };
}