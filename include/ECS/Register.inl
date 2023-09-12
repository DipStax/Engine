#include "ECS/Register.hpp"

namespace ecs
{
    template<class T, class _T>
    requires LsOp<T, T>
    void Register<T, _T>::add(const T &_index)
    {
        m_container.emplace(_index, _T());
    }

    template<class T, class _T>
    requires LsOp<T, T>
    void Register<T, _T>::pop(const T &_index)
    {
        if (m_container.contains(_index))
            m_container.erase(_index);
    }

    template<class T, class _T>
    requires LsOp<T, T>
    _T &Register<T, _T>::operator[](const T &_index)
    {
        return m_container[_index];
    }

    template<class T, class _T>
    requires LsOp<T, T>
    const _T &Register<T, _T>::operator[](const T &_index) const
    {
        return m_container[_index];
    }

    template<class T, class _T>
    requires LsOp<T, T>
    _T &Register<T, _T>::at(const T &_index)
    {
        return m_container[_index];
    }

    template<class T, class _T>
    requires LsOp<T, T>
    const _T &Register<T, _T>::at(const T &_index) const
    {
        return m_container[_index];
    }

    template<class T, class _T>
    requires LsOp<T, T>
    Register<T, _T>::iterator Register<T, _T>::begin()
    {
        return m_container.begin();
    }

    template<class T, class _T>
    requires LsOp<T, T>
    Register<T, _T>::const_iterator Register<T, _T>::cbegin() const
    {
        return m_container.cbegin();
    }

    template<class T, class _T>
    requires LsOp<T, T>
    Register<T, _T>::iterator Register<T, _T>::end()
    {
        return m_container.end();
    }

    template<class T, class _T>
    requires LsOp<T, T>
    Register<T, _T>::const_iterator Register<T, _T>::cend() const
    {
        return m_container.cend();
    }
}