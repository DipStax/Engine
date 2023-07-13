#pragma once

#include <memory>

namespace tester
{
    namespace priv {
        template<class T>
        struct CLNode
        {
            T data;
            std::shared_ptr<CLNode> next = nullptr;
            std::shared_ptr<CLNode> prev = nullptr;
        };
    }

    template<class T>
    class CircleList
    {
        public:
            CircleList() = default;
            ~CircleList() = default;

            [[nodiscard]] size_t size() const;

            void push_back(const T &_data);

            template<class ...Ts>
            void emplace(size_t _idx, Ts ..._args);
            template<class ...Ts>
            void emplace_back(Ts ..._args);

            void resize(size_t _size, T &_val = T());

            T &at(size_t _idx);
            const T &at(size_t _idx) const;

            T &operator[](size_t _idx);
            const T &operator[](size_t _idx) const;

            void erase(size_t _idx);

            void clear();

        private:
            std::shared_ptr<priv::CLNode> m_head;
            size_t m_size;
    };
}