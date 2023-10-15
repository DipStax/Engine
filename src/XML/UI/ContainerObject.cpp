#include "XML/UI/ContainerObject.hpp"

namespace eng::ui
{
    ContainerObject::ContainerObject(const std::string& _type, Vector2<uint32_t> m_size, ThreadPool& _tp)
        : PropObject(_tp), m_type(_type),
          Class(*this, "Class", ""), Height(*this, "Height", m_size.y), Width(*this, "Width", m_size.x)
    {
        ownProperty();
    }

    ContainerObject::ContainerObject(ContainerObject &&_obj) noexcept
        : PropObject(std::move(_obj)), m_content(std::move(_obj.m_content)), m_type(_obj.m_type),
          Class(std::move(_obj.Class)), Height(std::move(_obj.Height)), Width(std::move(_obj.Width))
    {
        ownProperty();
    }

    ContainerObject::~ContainerObject()
    {
        unregisterProperty<std::string>(m_bind_class);
        unregisterProperty<uint32_t>(m_bind_height);
        unregisterProperty<uint32_t>(m_bind_width);
    }

    const std::string &ContainerObject::getType() const
    {
        return m_type;
    }

    bool ContainerObject::have(const std::string &_class) const
    {
        return m_content.end() != std::find_if(m_content.begin(), m_content.end(), [_class](const ContainerObject& _obj) {
            return _class == _obj.Class;
        });
    }

    ContainerObject &ContainerObject::operator[](const std::string &_class)
    {
        return *std::find_if(m_content.begin(), m_content.end(), [_class] (const ContainerObject &_obj) {
            return _class == _obj.Class;
        });
    }

    const ContainerObject &ContainerObject::operator[](const std::string &_class) const
    {
        return *std::find_if(m_content.begin(), m_content.end(), [_class] (const ContainerObject &_obj) {
            return _class == _obj.Class;
        });
    }

    Vector2<uint32_t> ContainerObject::getSize() const
    {
        return { Width, Height };
    }

    void ContainerObject::addContent(ContainerObject &&_container)
    {
        m_content.push_back(std::move(_container));
    }

    void ContainerObject::deleteContent(const std::string &_class)
    {
        std::ignore = _class;

        // todo
    }

    void ContainerObject::ownProperty()
    {
        m_bind_class = registerProperty(Class);
        m_bind_height = registerProperty(Height);
        m_bind_width = registerProperty(Width);
    }
}