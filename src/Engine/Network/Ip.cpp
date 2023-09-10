#include <sstream>

#include "Engine/Network/Ip.hpp"

namespace eng
{
    Ip::Ip()
        : m_ip("0.0.0.0")
    {
    }

    void Ip::set(uint8_t _b1, uint8_t _b2, uint8_t _b3, uint8_t _b4)
    {
        std::ostringstream stream;

        stream << static_cast<uint16_t>(_b1) << "." << static_cast<uint16_t>(_b2) << "."
                << static_cast<uint16_t>(_b3) << "." << static_cast<uint16_t>(_b4);
        m_ip = stream.str();
    }

    void Ip::set(uint32_t _ip)
    {
        set((_ip >> 24) & 0xf, (_ip >> 16) & 0xf, (_ip >> 8) & 0xf, _ip & 0xf);
    }

    void Ip::set(const std::string &_ip)
    {
        m_ip = _ip;
    }

    const char *Ip::c_str() const
    {
        return m_ip.c_str();
    }

    uint8_t Ip::at(uint8_t _idx) const
    {
        std::istringstream stream;
        uint8_t n = 0;

        if (_idx > 3)
            return 255;
        stream.str(m_ip);
        for (uint8_t it = 0; it < _idx; it++) {
            stream >> n;
            if (it != _idx - 1) {
                std::string dot{};
                stream >> dot;
            }
        }
        return n;
    }

    Ip::operator uint32_t() const
    {
        return ((at(0) << 24) & 0xFF000000) + ((at(1) << 16) & 0xFF0000) + ((at(2) << 8) & 0xFF00) + (at(3) & 0xFF);
    }

    Ip::operator std::string() const
    {
        return m_ip;
    }
}