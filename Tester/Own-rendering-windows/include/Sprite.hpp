#pragma once

#include "VertexArray.hpp"
#include "Rect.hpp"
#include "IDrawable.hpp"
#include "Image.hpp"

namespace tester
{
    class Sprite : public IDrawable
    {
        public:
            Sprite() = default;
            ~Sprite() = default;

            void setImage(Image &_img);

            void setPosition(float _x, float _y);
            void setPosition(const Point2<float> &_pos);
            [[nodiscard]] Point2<float> getPosition() const;

            void setScale(const Point2<float> &_scale);
            void setScale(float _rh, float _rw);
            [[nodiscard]] Point2<float> getScale() const;

            void setImgRect(Rect &_rect);
            [[nodiscard]] Rect getImgRect() const;

        protected:
            void draw(RenderTarget &_target, const Image *_img) const;

        private:
            void processRect();

            Image m_img;

            VertexArray m_vertex;

            Rect m_rect;
            Point2<float> m_pos;
            Point2<float> m_scale = { 1, 1 };
    };
}