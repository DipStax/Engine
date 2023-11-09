#include "XML/UI/Object.hpp"

namespace eng::ui
{
    template<class ...Ts>
    Object<std::tuple<Ts...>>::Object(const std::string &_type, ThreadPool &_tp)
        : ObjectRegistre(_type), PropertyObject<std::tuple<Ts...>>(_tp),
          Width(*this, "Width", 0), Height(*this, "Height", 0)
    {
        ownProperty();
    }

    template<class ...Ts>
    Object<std::tuple<Ts...>>::Object(Object &&_obj) noexcept
        : ObjectRegistre(std::move(_obj)), PropertyObject<std::tuple<Ts...>>(std::move(_obj)),
          Width(std::move(_obj.Width)), Height(std::move(_obj.Height))
    {
        ownProperty();
    }

    template<class ...Ts>
    Object<std::tuple<Ts...>>::~Object()
    {
        unbindProperty<uint32_t>(m_bind_width);
        unbindProperty<uint32_t>(m_bind_height);
    }

    template<class ...Ts>
    Point2<uint32_t> Object<std::tuple<Ts...>>::getSize() const
    {
        return { Width, Height };
    }

    template<class ...Ts>
    void Object<std::tuple<Ts...>>::ownProperty()
    {
        registerProperty(Width);
        registerProperty(Height);

        m_bind_width = bindProperty<uint32_t>(Width);
        m_bind_height = bindProperty<uint32_t>(Height);

        m_inter_width = Width.subscribe([*this] (const Property<uint32_t>::Event &_val) {
            create(Width, Height);
        });
        m_inter_height = Height.subscribe([*this] (const Property<uint32_t>::Event &_val) {
            create(Width, Height);
        });
    }
}