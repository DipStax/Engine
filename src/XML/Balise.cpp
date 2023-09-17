#include <ostream>
#include <ranges>

#include "XML/Balise.hpp"

namespace eng::xml
{
    void Balise::setName(const std::string &_name)
    {
        m_name = _name;
    }

    void Balise::setType(Type _type)
    {
        m_type = _type;
    }

    void Balise::addValue(const Value &_value)
    {
        m_value.emplace(_value);
    }

    void Balise::addChildren(const Balise &_balise)
    {
        m_child.push_back(_balise);
    }

    void Balise::setContent(const std::string &_data)
    {
        m_content = _data;
    }

    Balise::Type Balise::getType() const
    {
        return m_type;
    }

    std::string &Balise::getName()
    {
        return m_name;
    }

    std::vector<Balise> &Balise::getChild()
    {
        return m_child;
    }

    std::string &Balise::getContent()
    {
        return m_content;
    }

    std::string &Balise::operator[](const std::string &_id)
    {
        return m_value[_id];
    }

#if defined(_DEBUG)
    PROJECT_API std::ostream& operator<<(std::ostream &_os, const Balise &_balise)
    {
        _os << "<" << _balise.m_name << " ";
        for (auto& [_key, _val] : _balise.m_value)
            _os << _key << "=" << _val << " ";
        if (_balise.m_type == Balise::Type::Single)
            _os << "/";
        _os << ">";

        if (_balise.m_type != Balise::Type::Single) {
            if (_balise.m_type != Balise::Type::NoSub) {
                if (_balise.m_type & Balise::Type::Children) {
                    _os << std::endl;
                    for (auto _child : _balise.m_child)
                        _os << _child << std::endl;
                }
                if (_balise.m_type == Balise::Type::Content) {
                    _os << std::endl << _balise.m_content << std::endl;
                }
            } else {
                _os << std::endl;
            }
            _os << "</" << _balise.m_name << ">" << std::endl;
        }
        return _os;
    }
#endif
}