#ifndef ENG_ZBUFFER_HPP
#define ENG_ZBUFFER_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Engine/Rendering/Color.hpp"
#include "Engine/Rendering/Triangle.hpp"
#include "Engine/Maths/Point2.hpp"
#include "Engine/Camera.hpp"

namespace eng
{
    class ZBuffer : public sf::Drawable
    {
        public:
            ZBuffer(Vector2<uint32_t> _size);
            ~ZBuffer() = default;

            void clear();

            void setSize(Vector2<uint32_t> _size);
            [[nodiscard]] const Vector2<uint32_t> &getSize() const;

            void draw(const Triangle &_tri, const sf::Image& _img);
            void draw(Point2<uint32_t> _pt, float _depth, Color _clr);

            void render();

        protected:
            void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

        private:
            [[nodiscard]] static Vector3<float> ZBuffe::getPointRatio(const Triangle &_tri, const Point2<float> &_pt);
            [[nodiscard]] static Color getPixel(const Triangle &_tri, const Vector3<float> &_ratio, const sf::Image &_img);
            [[nodiscard]] static float getDepth(const Triangle &_tri, const Vector3<float> &_ratio);

            Vector2<uint32_t> m_size;
            std::vector<float> m_depth;
            std::vector<Color> m_color;
            sf::Texture m_txtr;
            sf::Sprite m_sprite;
    };
}

#endif