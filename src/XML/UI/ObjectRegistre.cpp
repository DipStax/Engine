#include "XML/UI/ObjectRegistre.hpp"

namespace eng::ui
{
    ObjectRegistre::ObjectRegistre(const std::string& _type)
        : m_type(_type)
    {
    }

    ObjectRegistre::ObjectRegistre(ObjectRegistre &&_obj) noexcept
        : m_type(std::move(_obj.m_type))
    {
    }

    const std::string &ObjectRegistre::getType() const
    {
        return m_type;
    }

    void ObjectRegistre::addContent(std::shared_ptr<BaseObject> _obj)
    {
        m_content.push_back(_obj);
    }
}