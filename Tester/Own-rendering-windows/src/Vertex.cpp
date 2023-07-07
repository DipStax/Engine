#include "Vertex.hpp"

namespace tester
{
    Vertex::Vertex(Type _type, size_t _n)
        : m_type(_type), m_pos(_n)
    {
    }

    void Vertex::resize(size_t _n)
    {
        m_pos.resize(_n);
    }

    void Vertex::append(const Pixel &_px)
    {
        m_pos.emplace_back(_px);
    }

    Vertex::Type Vertex::getType() const
    {
        return m_type;
    }

    bool Vertex::draw(RenderWindow &_win) const
    {
        if (!m_pos.empty())
            _win.draw(m_pos.data(), m_pos.size(), m_type);
        return !m_pos.empty();
    }
}