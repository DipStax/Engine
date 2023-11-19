#pragma once

#include "XML/Factory/Balise.hpp"
#include "XML/UI/Object.hpp"
#include "XML/Object/Rectangle.hpp"
#include "Engine/Rendering/IDrawable.hpp"

namespace eng::ui
{
    template<class ...Ts>
    class Context : public IDrawable
    {
        public:
            Context(ThreadPool &_tp, SysEventPool &_sys_ep, Point2<uint32_t> _size = Point2<uint32_t>{ 0, 0 });
            ~Context() = default;

            void load(const std::string &_path);

            [[nodiscard]] Point2<uint32_t> getSize() const;
            void setSize(const Point2<uint32_t> &_size) const;
            void setSize(uint32_t _height, uint32_t _width) const;

            void display();

        protected:
            void draw(RenderTarget &_target, const Texture *_txtr) const;

        private:
            Factory::Balise<std::tuple<Ts...>, std::tuple<Rectangle<Ts...>>> m_fac;

            std::shared_ptr<ui::Object<Ts...>> m_obj;

            Point2<uint32_t> m_size;

            EventPool<Ts...> m_cus_ep;
            SysEventPool &m_sys_ep;

            ThreadPool &_tp;
    };
}

#include "XML/UI/System/Context.hpp"