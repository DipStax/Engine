#include "XML/UI/AssetObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    requires ContainIn<Display, Ts...>
    void AssetObject<Ts...>::display()
    {
        for (fn_draw _fn : m_draw)
            _fn(*this, nullptr);
        m_txtr.load(getData(), getSize().x * getSize().y);
        m_sprite.setTexture(m_txtr);
        raise<Display>({ getSize() });
    }

    template<class ...Ts>
    requires ContainIn<Display, Ts...>
    void AssetObject<Ts...>::draw(RenderTarget &_target, const Texture *_txtr) const
    {
        std::ignore = _txtr;

        _target.draw(m_sprite, &m_txtr);
    }

    template<class ...Ts>
    requires ContainIn<Display, Ts...>
    void AssetObject<Ts...>::registerDraw(fn_draw _draw)
    {
        m_draw.push_back(_draw);
    }
}