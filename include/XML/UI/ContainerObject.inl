#include "XML/UI/ContainerObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    ContainerObject<ts...>::ContainerObject(const std::string& _type, Vector2<uint32_t> m_size, ThreadPool& _tp)
        : PropObject(_tp), m_type(_type),
          Class(*this, "Class", ""), Height(*this, "Height", m_size.y), Width(*this, "Width", m_size.x)
    {
        ownProperty();
    }

    template<class ...Ts>
    ContainerObject<ts...>::ContainerObject(ContainerObject &&_obj) noexcept
        : PropObject(std::move(_obj)), m_content(std::move(_obj.m_content)), m_type(_obj.m_type),
          Class(std::move(_obj.Class)), Height(std::move(_obj.Height)), Width(std::move(_obj.Width))
    {
        ownProperty();
    }

    template<class ...Ts>
    ContainerObject<ts...>::~ContainerObject()
    {
        unregisterProperty<std::string>(m_bind_class);
        unregisterProperty<uint32_t>(m_bind_height);
        unregisterProperty<uint32_t>(m_bind_width);
    }

    template<class ...Ts>
    const std::string &ContainerObject<ts...>::getType() const
    {
        return m_type;
    }

    template<class ...Ts>
    bool ContainerObject<ts...>::have(const std::string &_class) const
    {
        return m_content.end() != std::find_if(m_content.begin(), m_content.end(), [_class](const ContainerObject& _obj) {
            return _class == _obj.Class;
        });
    }

    template<class ...Ts>
    ContainerObject &ContainerObject<ts...>::operator[](const std::string &_class)
    {
        return *std::find_if(m_content.begin(), m_content.end(), [_class] (const ContainerObject &_obj) {
            return _class == _obj.Class;
        });
    }

    template<class ...Ts>
    const ContainerObject &ContainerObject<ts...>::operator[](const std::string &_class) const
    {
        return *std::find_if(m_content.begin(), m_content.end(), [_class] (const ContainerObject &_obj) {
            return _class == _obj.Class;
        });
    }

    template<class ...Ts>
    Vector2<uint32_t> ContainerObject<ts...>::getSize() const
    {
        return { Width, Height };
    }

    template<class ...Ts>
    void ContainerObject<ts...>::addContent(ContainerObject &&_container)
    {
        m_content.push_back(std::move(_container));
    }

    template<class ...Ts>
    void ContainerObject<ts...>::deleteContent(const std::string &_class)
    {
        std::ignore = _class;

        // todo
    }

    template<class ...Ts>
    void onSizeChange(const eng::Property<uin32_t>::Event &_size)
    {
        eng::Point2<uint32_t> size { Height, Width };

        if (_size.name == "Height")
            size.y = _size.value;
        else if (_size.name == "Width")
            size.x = _size.value;
        create(size.x, size.y);
    }

    template<class ...Ts>
    void ContainerObject<ts...>::ownProperty()
    {
        registerProperty(Class);
        registerProperty(Height);
        registerProperty(Width);

        m_bind_class = bindProperty(Class);
        m_bind_height = bindProperty(Height);
        m_bind_width = bindProperty(Width);
    }
}