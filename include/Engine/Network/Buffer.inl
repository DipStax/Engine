#include "Engine/Network/Buffer.hpp"

namespace eng
{
    template<class T>
    Buffer::Buffer(T &_data)
    {
        (*this) << _data;
    }

    template<NumericType T>
    Buffer &Buffer::operator<<(const T &_data)
    {
        append(&_data, sizeof(T));
        return *this;
    }

    template<NumericType T>
    Buffer &Buffer::operator>>(T &_data)
    {
        std::memcpy(&_data, data() + size() - sizeof(T), sizeof(T));
        m_data.erase(m_data.end() - sizeof(T), m_data.end());
        return *this;
    }
}