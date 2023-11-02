#include <ostream>
#include <ranges>

#include "XML/Balise.hpp"

namespace eng::xml
{
    void Balise::setType(const std::string &_type)
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

    std::string &Balise::getType()
    {
        return m_type;
    }

    const std::string &Balise::getType() const
    {
        return m_type;
    }

    std::vector<Balise> &Balise::getChild()
    {
        return m_child;
    }

    const std::vector<Balise> &Balise::getChild() const
    {
        return m_child;
    }

    std::string &Balise::operator[](const std::string &_name)
    {
        return m_value[_name];
    }

    std::ostream &Balise::writeBalise(std::ostream &_os, const Balise &_balise, size_t _it)
    {
        std::string marge(_it * 4, ' ');
        bool child = _balise.getChild().empty();

        _os << marge << "<" << _balise.m_type << " ";
        for (auto& [_key, _val] : _balise.m_value)
            _os << _key << "=\"" << _val << "\" ";
        if (child) {
            _os << "/>" << std::endl;
            for (auto _child : _balise.m_child)
                writeBalise(_os, _child, _it + 1) << std::endl;
            _os << marge << "</" << _balise.m_type;
        }
        _os << ">";
        return _os;
    }

    PROJECT_API std::ostream& operator<<(std::ostream &_os, const Balise &_balise)
    {
        Balise::writeBalise(_os, _balise);
        return _os;
    }
}