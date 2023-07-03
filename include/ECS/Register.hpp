#ifndef ECS_REGISTER_HPP
#define ECS_REGISTER_HPP

#include <map>
#include <tuple>
#include <optional>

#include "Tool/PreProcessing.hpp"

namespace ecs
{
    template<KeyType T, class _T>
    class Register
    {
        public:
            using ContainerType = std::map<T, _T>;
            using iterator = ContainerType::iterator;
            using const_iterator = ContainerType::iterator;

            Register() = default;
            ~Register() = default;

            void add(const T &_index);
            void pop(const T &_index);

            _T &at(const T &_index);
            const _T &at(const T &_index) const;
            _T &operator[](const T &_index);
            const _T &operator[](const T &_index) const;


            iterator begin();
            const_iterator cbegin() const;
            iterator end();
            const_iterator cend() const;

        private:
            ContainerType m_container;
    };
}

#include "ECS/Register.inl"

#endif