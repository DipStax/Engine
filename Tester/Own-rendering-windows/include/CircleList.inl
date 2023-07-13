#include "CircleList.hpp"

namespace tester
{
    template<class T>
    size_t CircleList<T>::size() const
    {
        return m_size;
    }

    template<class T>
    void CircleList<T>::push_back(const T &_data)
    {
        std::shared_ptr<priv::CLNode> node = std::make_shared<priv::CLNode>({ _data });

        if (m_head) {
            node->next = m_head;
            node->prev = m_head->prev;
            m_head->prev->next = node;
            m_head->prev = node;
        } else {
            m_head = node;
            m_head->next = m_head;
            m_head->prev = m_head;
        }
        m_size++;
    }

    template<class T>
    template<class ...Ts>
    void CircleList<T>::emplace(size_t _idx, Ts ..._args)
    {
        std::shared_ptr<priv::CLNode> ptr = m_head;
        std::shared_ptr<priv::CLNode> node = std::make_shared<priv::CLNode>({ _data });

        if (_idx == 0) {
            push_back(T(std::forward<Ts>(_args)...));
            m_head = m_head->prev;
            return;
        }
        for (size_t it = 0; it < _idx; it++, ptr = ptr->next) {}
        node->next = ptr;
        node->prev = ptr->prev;
        ptr->prev->next = node;
        ptr->prev = node;
    }

    template<class T>
    template<class ...Ts>
    void CircleList<T>::emplace_back(Ts ..._args)
    {
        emplace(m_size++, std::forward<Ts>(_args)...);
    }

    template<class T>
    void CircleList<T>::resize(size_t _size, T &_val)
    {
        if (_size > m_size) {
            for (size_t it = 0; it < _size - m_size; it++)
                push_back(_val);
        } else {
            while(m_size != _size)
                erase(m_size - 1);
        }
    }

    template<class T>
    T &CircleList<T>::at(size_t _idx)
    {
        std::shared_ptr<priv::CLNode> ptr = m_head;

        for (size_t it = 0; it < _idx; it++, ptr = ptr->next) {}
        return ptr->data;
    }

    template<class T>
    const T &CircleList<T>::at(size_t _idx) const
    {
        std::shared_ptr<priv::CLNode> ptr = m_head;

        for (size_t it = 0; it < _idx; it++, ptr = ptr->next) {}
        return ptr->data;
    }

    template<class T>
    T &CircleList<T>::operator[](size_t _idx)
    {
        return at(_idx);
    }

    template<class T>
    const T &CircleList<T>::operator[](size_t _idx) const
    {
        return at(_idx);
    }

    template<class T>
    void CircleList<T>::erase(size_t _idx)
    {
        // memory leak ?
        std::shared_ptr<priv::CLNode> ptr = m_head;

        if (m_size == 0)
            return;
        if (_idx == 0) {
            if (m_size > 1) {
                m_head->next->prev = m_head->prev;
                m_head->prev->next = m_head->next;
                m_head = m_head->next;
            }
            ptr->next = nullptr;
            ptr->prev = nullptr;
            if (m_size == 1)
                m_head = nullptr;
        } else {
            for (size_t it = 0; it < _idx; it++, ptr = ptr->next) {}
            ptr->next->prev = ptr->prev;
            ptr->prev->next = ptr->next;
        }
        m_size--;
    }

    template<class T>
    void CircleList<T>::clear()
    {
        while (m_size)
            erase(0);
    }
}