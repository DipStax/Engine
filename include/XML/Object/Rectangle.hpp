#pragma once

#include "Engine/Rendering/Color.hpp"
#include "XML/UI/Object.hpp"

namespace eng::ui
{
    template<class ...Ts>
    class PROJECT_API Rectangle : public Object<Ts...>
    {
        public:
            Rectangle(const std::string &_type, eng::ThreadPool &_tp);
            Rectangle(Rectangle &&_obj) noexcept;
            ~Rectangle();

            Property<uint32_t> PositionX;
            Property<uint32_t> PositionY;
            [[nodiscard]] Point2<uint32_t> getPosition() const;

            Property<uint32_t> OriginX;
            Property<uint32_t> OriginY;
            [[nodiscard]] Point2<uint32_t> getOrigin() const;

            Property<float> ScaleX;
            Property<float> ScaleY;
            [[nodiscard]] Point2<float> getScale() const;

            Property<float> Rotation;

            Property<Color> Color;

        protected:
            void draw(RenderTarget &_target, const Texture *_txtr) const override;

        private:
            void ownProperty();

            void processRect();
            void buildVertex();

            void onPositionChange(const Property<uint32_t>::Event &_pos);
            void onOrigineChange(const Property<uint32_t>::Event &_ori);
            void onRotationChange(const Property<float>::Event &_rot);

            PropertyBind<uint32_t> m_bind_posx;
            PropertyBind<uint32_t> m_bind_posy;
            PropertyBind<uint32_t> m_bind_originx;
            PropertyBind<uint32_t> m_bind_originy;
            PropertyBind<float> m_bind_scalex;
            PropertyBind<float> m_bind_scaley;
            PropertyBind<float> m_bind_rotation;
            PropertyBind<eng::Color> m_bind_color;

            VertexArray m_vertex{};

            Rect m_rect;
    };
}