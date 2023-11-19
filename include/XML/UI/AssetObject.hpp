#pragma once

#include <functional>
#include <vector>

#include "Engine/Rendering/RenderTarget.hpp"
#include "XML/UI/TransformableObject.hpp"
#include "XML/UI/Event/Event.hpp"

namespace eng::ui
{
    template<class ...Ts>
    requires ContainIn<Display, Ts...>
    class AssetObject : public RenderTarget, public IDrawable, public TransformableObject<Ts...>
    {
        public:
            AssetObject(SysEventPool &_ep_sys, EventPool<Ts...> &_ep_cus, ThreadPool &_tp);
            ~AssetObject() = default;

            using fn_draw = std::function<void (RenderTarget &, const Texture *) const>;

            void display();

        protected:
            void draw(RenderTarget &_target, const Texture *_txtr) const;
            void registerDraw(fn_draw _draw);

        private:
            std::vector<fn_draw> m_draw;
            Texture m_txtr;
            Sprite m_sprite;
    };
}

#include "XML/UI/AssetObject.inl"