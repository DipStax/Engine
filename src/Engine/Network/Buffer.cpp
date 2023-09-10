#include "Engine/Network/Buffer.hpp"

namespace eng
{
    Buffer::Buffer(size_t _size)
    {
        resize(_size);
    }

    void Buffer::resize(size_t _size)
    {
        m_data.resize(_size, 0);
    }

    size_t Buffer::size() const
    {
        return m_data.size();
    }

    const uint8_t *Buffer::data() const
    {
        return m_data.data();
    }

    uint8_t* Buffer::data()
    {
        return m_data.data();
    }

    void Buffer::append(const void *_data, size_t _size)
    {
        size_t size = m_data.size();

        m_data.resize(size + _size, 0);
        std::memcpy(&m_data[size], _data, _size);
    }

    Buffer &Buffer::operator<<(const Buffer &_buffer)
    {
        (*this) << _buffer.size();
        append(_buffer.data(), _buffer.size());
        return *this;
    }

    Buffer &Buffer::operator>>(Buffer &_buffer)
    {
        size_t sbuff = 0;

        (*this) >> sbuff;
        _buffer.m_data.insert(_buffer.m_data.begin(), m_data.end() - sbuff, m_data.end());
        m_data.erase(m_data.end() - sbuff, m_data.end());
        return *this;
    }

    Buffer &Buffer::operator<<(const std::string_view &_str)
    {
        (*this) << _str.size();
        append(_str.data(), _str.size());
        return *this;
    }

    Buffer &Buffer::operator<<(const char *_str)
    {
        size_t sstr = std::strlen(_str);

        (*this) << sstr;
        append(_str, sstr);
        return (*this);
    }

    Buffer &Buffer::operator>>(std::string &_str)
    {
        size_t sstr = 0;

        (*this) >> sstr;
        _str.resize(sstr);
        std::memcpy(_str.data(), &m_data[size() - sstr], sstr);
        m_data.erase(m_data.end() - sstr, m_data.end());
        return *this;
    }

    void Buffer::clear()
    {
        m_data.clear();
    }
}