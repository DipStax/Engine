#include "XML/UI/BaseObject.hpp"

namespace eng::ui
{
    BaseObject::BaseObject()
    {
        create(0, 0, 32);
    }

    void BaseObject::draw(RenderTarget &_target, const Texture *_txtr) const
    {
        // cache?
        Texture txtr;
        Sprite sprite;

        txtr.load(getData(), getSize());
        sprite.setTexture(txtr);
        _target.draw(sprite, _txtr);
    }
}