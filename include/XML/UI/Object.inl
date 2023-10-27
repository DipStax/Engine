#include "XML/UI/Object.hpp"

namespace eng::ui
{
    template<class ...Ts>
    Object<std::tuple<Ts...>>::Object(const std::string &_type, ThreadPool &_tp)
        : ContainerObject(_type), PropertyObject<std::tuple<Ts...>>(_tp), Class(*this, "Class", ""),
          Width(*this, "Width", 0), Height(*this, "Height", 0)
    {
        ownProperty();
    }

    template<class ...Ts>
    Object<std::tuple<Ts...>>::Object(Object &&_obj) noexcept
        : ContainerObject(std::move(_obj)), PropertyObject<std::tuple<Ts...>>(std::move(_obj)),
          Class(std::move(_obj.Class)), Width(std::move(_obj.Width)), Height(std::move(_obj.Height))
    {
        ownProperty();
    }

    template<class Ts...>
    Object<std::tuple<Ts...>>::~Object()
    {
        unbindProperty<std::string>(m_bind_class);
        unbindProperty<uint32_t>(m_bind_width);
        unbindProperty<uint32_t>(m_bind_height);
    }

    template<class Ts...>
    Point2<uint32_t> Object<std::tuple<Ts...>>::getSize() const
    {
        return { Width, Height };
    }

    template<class Ts...>
    void Object<std::tuple<Ts...>>::ownProperty()
    {
        registerProperty(Class);
        registerProperty(Width);
        registerProperty(Height);

        m_bind_class = bindProperty(Class);
        m_bind_width = bindProperty(Width);
        m_bind_height = bindProperty(Height);

        m_inter_class = Class.subscribe([*this] (const Property<std::string>::Event &_val) {
            setClass(_val.value);
        });
        m_inter_width = Width.subscribe([*this] (const Property<uint32_t>::Event &_val) {
            create(Width, Height);
        });
        m_inter_height = Height.subscribe([*this] (const Property<uint32_t>::Event &_val) {
            create(Width, Height);
        });
    }
}