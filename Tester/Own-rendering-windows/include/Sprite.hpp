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

            void setPosition(uint32_t _x, uint32_t _y);
            void setPosition(const Point2<uint32_t> &_pos);
            [[nodiscard]] Point2<uint32_t> getPosition() const;

            void setScale(const Point2<uint32_t> &_scale);
            void setScale(uint32_t _rh, uint32_t _rw);
            [[nodiscard]] Point2<uint32_t> getScale() const;

            void setImgRect(Rect &_rect);
            [[nodiscard]] Rect getImgRect() const;

        protected:
            void draw(RenderTarget &_target, Image *_img) const;

        private:
            void generateVertex();

            Image m_img;

            VertexArray m_vertex;

            Rect m_rect;
            Point2<uint32_t> m_pos;
            Point2<uint32_t> m_scale;
    };
}