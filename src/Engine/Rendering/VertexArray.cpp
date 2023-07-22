#include "Engine/Rendering/RenderTarget.hpp"
#include "Engine/Rendering/VertexArray.hpp"

namespace eng
{
    VertexArray::VertexArray(size_t _n)
        : m_pos(_n)
    {
    }

    void VertexArray::setType(Type _type)
    {
        m_type = _type;
    }

    VertexArray::Type VertexArray::getType() const
    {
        return m_type;
    }

    void VertexArray::resize(size_t _n)
    {
        m_pos.resize(_n);
    }

    void VertexArray::append(const Vertex &_px)
    {
        m_pos.emplace_back(_px);
    }

    Vertex &VertexArray::operator[](size_t _idx)
    {
        return m_pos[_idx];
    }

    void VertexArray::clear()
    {
        m_pos.clear();
    }

    void VertexArray::draw(RenderTarget &_target, const Texture *_txtr) const
    {
        if (!m_pos.empty()) {
            if (_txtr)
                _target.draw(m_pos.data(), m_pos.size(), _txtr);
            else
                _target.draw(m_pos.data(), m_pos.size(), m_type);
        }
    }
}