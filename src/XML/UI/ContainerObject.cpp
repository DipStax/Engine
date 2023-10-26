#include "XML/UI/ContainerObject.hpp"

namespace eng::ui
{
    ContainerObject::ContainerObject(const std::string& _type)
        : m_type(_type)
    {
    }

    ContainerObject::ContainerObject(ContainerObject &&_obj) noexcept
        : m_type(std::move(_obj.m_type)), m_class(std::move(_obj.m_class))
    {
    }

    void ContainerObject::setClass(const std::string &_class)
    {
        m_class = _class;
    }

    const std::string &ContainerObject::getType() const
    {
        return m_type;
    }

    bool ContainerObject::have(const std::string &_class) const
    {
        return m_content.end() != std::find_if(m_content.begin(), m_content.end(), [_class](const ContainerObject& _obj) {
            return _class == _obj.getClass();
        });
    }

    ContainerObject &ContainerObject::operator[](const std::string &_class)
    {
        return *std::find_if(m_content.begin(), m_content.end(), [_class] (const ContainerObject &_obj) {
            return _class == _obj.getClass();
        });
    }

    const ContainerObject &ContainerObject::operator[](const std::string &_class) const
    {
        return *std::find_if(m_content.begin(), m_content.end(), [_class] (const ContainerObject &_obj) {
            return _class == _obj.getClass();
        });
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
}