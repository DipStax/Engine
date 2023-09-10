#pragma once

#include <vector>
#include <string_view>

#include "Tool/Export.hpp"
#include "Tool/PreProcessing.hpp"

namespace eng
{
    class PROJECT_API Buffer
    {
        public:
            Buffer(size_t _size = 0);
            template<class T>
            Buffer(T &_data);
            ~Buffer() = default;

            void resize(size_t _size);

            [[nodiscard]] size_t size() const;
            [[nodiscard]] const uint8_t* data() const;
            [[nodiscard]] uint8_t *data();

            void append(const void *_data, size_t _size);

            Buffer &operator<<(const Buffer &_buffer);
            Buffer &operator>>(Buffer &_buffer);

            template<NumericType T>
            Buffer &operator<<(const T &_data);
            template<NumericType T>
            Buffer &operator>>(T &_data);

            Buffer &operator<<(const std::string_view &_str);
            Buffer &operator<<(const char *_str);
            Buffer &operator>>(std::string &_str);


            void clear();

        private:
            std::vector<uint8_t> m_data;
    };
}

#include "Engine/Network/Buffer.inl"