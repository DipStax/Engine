#pragma once

#include <map>
#include <tuple>
#include <optional>

#include "Tool/PreProcessing.hpp"

namespace ecs
{
    template<class T, class _T>
    requires LsOp<T, T>
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