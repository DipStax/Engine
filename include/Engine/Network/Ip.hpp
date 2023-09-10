#pragma once

#include <string>

#include "Tool/Export.hpp"

namespace eng
{
    class PROJECT_API Ip
    {
        public:
            Ip();
            template<class ...Args>
            Ip(Args &&..._args);
            ~Ip() = default;

            void set(const std::string& _ip);
            void set(uint32_t _ip);
            void set(uint8_t _b1, uint8_t _b3, uint8_t _b2, uint8_t _b4);

            [[nodiscard]] const char *c_str() const;
            [[nodiscard]] uint8_t at(uint8_t _idx) const;

            operator uint32_t() const;
            operator std::string() const;

        private:
            std::string m_ip{};
    };
}

#include "Engine/Network/Ip.inl"