#pragma once

#define RECTANGLE_EVENT float, eng::Color

#include "Engine/Rendering/Color.hpp"
#include "Engine/Rendering/IDrawable.hpp"
#include "XML/UI/ContainerObject.hpp"

namespace eng::ui
{
    using RectangleEvent = typename single_type<RECTANGLE_EVENT>::type;

    class Rectangle : public ContainerObject<RectangleEvent>, public eng::IDrawable
    {
        public:
            Rectangle(const std::string &_type, eng::Vector2<uint32_t> m_size, eng::ThreadPool &_tp);
            Rectangle(const Rectangle &&_obj) noexcept;
            ~Rectangle();

            eng::Property<uint32_t> PositionX;
            eng::Property<uint32_t> PositionY;
            [[nodiscard]] eng::Point2<uint32_t> getPosition() const;

            eng::Property<uint32_t> OriginX;
            eng::Property<uint32_t> OriginY;
            [[nodiscard]] eng::Point2<uint32_t> getOrigin() const;

            eng::Property<float> ScaleX;
            eng::Property<float> ScaleY;
            [[nodiscard]] eng::Point2<float> getScale() const;

            eng::Property<float> Rotation;

            eng::Property<eng::Color> Color;

        protected:
            void draw(RenderTarget &_target, const Texture *_txtr) const override;

        private:
            void processRect();
            void buildVertex();

            void ownProperty();

            void onPositionChange(const Property<uint32_t>::Event &_pos);
            void onOrigineChange(const Property<uint32_t>::Event &_ori);
            void onRotationChange(const Property<float>::Event &_rot);

            Trigger<uint32_t>::sTask m_bind_posx;
            Trigger<uint32_t>::sTask m_bind_posy;
            Trigger<uint32_t>::sTask m_bind_originx;
            Trigger<uint32_t>::sTask m_bind_originy;
            Trigger<float>::sTask m_bind_scalex;
            Trigger<float>::sTask m_bind_scaley;
            Trigger<float>::sTask m_bind_rotation;
            Trigger<eng::Color>::sTask m_bind_color;

            VertexArray m_vertex{};

            Rect m_rect;
    };
}