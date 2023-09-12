#pragma once

#include <vector>

#include "Engine/Rendering/Vertex.hpp"
#include "Engine/Rendering/IDrawable.hpp"

namespace eng
{
    class PROJECT_API VertexArray : public IDrawable
    {
        public:
            enum class Type
            {
                point,
                polygone,
                line
            };

            VertexArray(size_t _n = 0);
            ~VertexArray() = default;

            void setType(Type _type);
            [[nodiscard]] Type getType() const;

            void resize(size_t _n);
            void append(const Vertex &_px);

            [[nodiscard]] Vertex &operator[](size_t _idx);

            void clear();

        protected:
            void draw(RenderTarget &_target, const Texture *_txtr) const;

        private:
            std::vector<Vertex> m_pos;
            Type m_type = Type::point;
    };
}