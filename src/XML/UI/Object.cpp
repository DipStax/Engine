#include "XML/UI/Object.hpp"

namespace eng::ui
{
    Object::Object()
    {
        create(0, 0, 32);
    }

    void Object::draw(RenderTarget &_target, const Texture *_txtr) const
    {
        // cache?
        Texture txtr;
        Sprite sprite;

        txtr.load(getData(), getSize());
        sprite.setTexture(txtr);
        _target.draw(sprite, _txtr);
    }
}