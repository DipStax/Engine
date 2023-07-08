#pragma once

#include <vector>

#include "Pixel.hpp"
#include "IDrawable.hpp"

namespace tester
{
    class Vertex : public IDrawable
    {
        public:
            enum Type
            {
                pixel,
                polygone,
                line
            };

            Vertex(Type _type, size_t _n);
            ~Vertex() = default;

            void resize(size_t _n);
            void append(const Pixel &_px);

            [[nodiscard]] Type getType() const;
            [[nodiscar]] Pixel &operator[](size_t _idx);

        protected:
            void draw(RenderTarget &_target) const;

        private:
            std::vector<Pixel> m_pos;
            Type m_type = Type::pixel;
    };
}