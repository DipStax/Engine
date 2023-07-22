#ifndef ENG_REND_SPRITE_HPp
#define ENG_REND_SPRITE_HPp

#include "VertexArray.hpp"
#include "Rect.hpp"
#include "Engine/Rendering/IDrawable.hpp"
#include "Engine/Rendering/Texture.hpp"

namespace eng
{
    class Sprite : public IDrawable
    {
        public:
            Sprite() = default;
            ~Sprite() = default;

            void setTexture(Texture &_img);

            void setPosition(float _x, float _y);
            void setPosition(const Point2<float> &_pos);
            [[nodiscard]] Point2<float> getPosition() const;

            void setScale(const Point2<float> &_scale);
            void setScale(float _rh, float _rw);
            [[nodiscard]] Point2<float> getScale() const;

            void setTxtrRect(Rect &_rect);
            [[nodiscard]] Rect getTxtrRect() const;

        protected:
            void draw(RenderTarget &_target, const Image *_img) const;

        private:
            void processRect();

            Texture m_txtr;

            VertexArray m_vertex;

            Rect m_rect;
            Point2<float> m_pos;
            Point2<float> m_scale = { 1, 1 };
    };
}

#endif