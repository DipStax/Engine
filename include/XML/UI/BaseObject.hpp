#pragma once

#include "Engine/Event/EventPool.hpp"
#include "Engine/Rendering/Sprite.hpp"
#include "Engine/Rendering/RenderTexture.hpp"

#include "XML/UI/ObjectRegistre.hpp"
#include "XML/UI/PropertyRegistre.hpp"

namespace eng::ui
{
    class BaseObject : public IDrawable, protected RenderTarget, public PropertyRegistre, public ObjectRegistre
    {
        public:
            BaseObject(const std::string &_type);
            ~BaseObject() = default;

        protected:
            void draw(RenderTarget &_target, const Texture *_txtr) const override;
    };
}