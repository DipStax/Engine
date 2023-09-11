#include "Engine/Event/Property.hpp"

namespace eng
{
    template<class T>
    template<class ...Ts>
    Property<T>::Property(EventPool<PropertyEvent> &_ep, std::string_view &_name, Ts &&..._args)
        : m_name(_name), m_ep(_ep), m_value(std::forward<Ts>(_args)...)
    {
    }

    template<class T>
    void Property<T>::trigger()
    {
        m_ep.raise<PropertyEvent>({ m_name, m_value });
    }

    template<class T>
    const std::string &Property<T>::getName() const
    {
        return m_name;
    }

#pragma region Property operator

    template<class T>
    template<AssignOp _T>
    Property<T> &Property<T>::operator=(const _T &_val)
    {
        m_value = _val;
        trigger();
    }

    template<class T>
    template<AssignOp _T>
    Property<T> &Property<T>::operator=(const Property<_T> &_val)
    {
        m_value = _val;
        trigger();
    }

    template<class T>
    Property<T>::operator T&()
    {
        return m_value;
    }

    template<class T>
    Property<T>::operator T() const
    {
        return m_value;
    }

    template<class T>
    template<EqOp _T>
    bool Property<T>::operator==(const _T &_val) const
    {
        return m_value == _val;
    }

    template<class T>
    template<NEqOp _T>
    bool Property<T>::operator!=(const _T &_val) const
    {
        return m_value != _val;
    }

    template<class T>
    template<LsOp _T>
    bool Property<T>::operator<(const _T &_val) const
    {
        return m_value < _val;
    }

    template<class T>
    template<GtOp _T>
    bool Property<T>::operator>(const _T &_val) const
    {
        return m_value > _val;
    }

    template<class T>
    template<LsEqOp _T>
    bool Property<T>::operator<=(const _T &_val) const
    {
        return m_value <= _val;
    }

    template<class T>
    template<GtEqOp _T>
    bool Property<T>::operator>=(const _T &_val) const
    {
        return m_value >= _val;
    }

    template<class T>
    template<GlobCompOp _T>
    bool Property<T>::operator<=>(const _T &_val) const
    {
        return m_value <=> _val;
    }

    template<class T>
    template<AssignAddOp _T>
    Property<T> Property<T>::operator+=(const _T &_val)
    {
        m_value += _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignSubOp _T>
    Property<T> Property<T>::operator-=(const _T &_val)
    {
        m_value -= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignMulOp _T>
    Property<T> Property<T>::operator*=(const _T &_val)
    {
        m_value *= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignDivOp _T>
    Property<T> Property<T>::operator/=(const _T &_val)
    {
        m_value /= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignModOp _T>
    Property<T> Property<T>::operator%=(const _T &_val)
    {
        m_value %= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignBitAndOp _T>
    Property<T> Property<T>::operator&=(const _T &_val)
    {
        m_value &= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignBitOrOp _T>
    Property<T> Property<T>::operator|=(const _T &_val)
    {
        m_value |= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignBitXorOp _T>
    Property<T> Property<T>::operator^=(const _T &_val)
    {
        m_value ^= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignLShiftOp _T>
    Property<T> Property<T>::operator<<=(const _T &_val)
    {
        m_value <<= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignRShiftOp _T>
    Property<T> Property<T>::operator>>=(const _T &_val)
    {
        m_value >>= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<PreIncOp _T>
    Property<T> Property<T>::operator++()
    {
        m_value++;
        trigger();
        return *this;
    }

    template<class T>
    template<PostIncOp _T>
    Property<T> Property<T>::operator++(int)
    {
        ++m_value;
        return *this;
    }
    template<class T>
    template<PreDecOp _T>
    Property<T> Property<T>::operator--()
    {
        m_value--;
        trigger();
        return *this;
    }

    template<class T>
    template<PostDecOp _T>
    Property<T> Property<T>::operator--(int)
    {
        --m_value;
        return *this;
    }

#pragma endregion
}