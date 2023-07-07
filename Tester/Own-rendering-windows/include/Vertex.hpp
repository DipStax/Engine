#pragma once

#include <vector>

#include "Pixel.hpp"
#include "IDrawable.hpp"

namespace tester
{
    class Vertex : public IDrawable
    {
        public:
            enum class Type
            {
                Pixel,
                Polygone,
                Line
            };

            Vertex(Type _type, size_t _n);
            ~Vertex() = default;

            void resize(size_t _n);
            void append(const Pixel &_px);

            [[nodiscard]] Type getType() const;

        protected:
            bool draw(RenderWindow &_win) const;

        private:
            std::vector<Pixel> m_pos;
            Type m_type = Type::Pixel;
    };
}

#include "RenderWindow.hpp"