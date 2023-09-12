#include "Engine/Event/Property.hpp"

namespace eng
{
    template<class T>
    Property<T>::Property(PropEventPool &_ep, const std::string &_name, T &_value)
        : m_name(_name), m_ep(_ep), m_value(_value)
    {
    }

    template<class T>
    template<class ...Ts>
    Property<T>::Property(PropEventPool&_ep, const std::string &_name, Ts &&..._args)
        : m_name(_name), m_ep(_ep), m_value(std::forward<Ts>(_args)...)
    {
    }

    template<class T>
    Property<T>::PropTrigger::sTask Property<T>::subscribe(PropTrigger::Task _task)
    {
        return m_ep.subscribe<PropertyEvent>(_task);
    }

    template<class T>
    void Property<T>::unsubscribe(PropTrigger::sTask _task)
    {
        m_ep.unsubscribe<PropertyEvent>(_task);
    }

    template<class T>
    void Property<T>::trigger()
    {
        m_ep.raise<PropertyEvent>({ m_name, std::make_any<T>(m_value) });
    }

    template<class T>
    const std::string &Property<T>::getName() const
    {
        return m_name;
    }

#pragma region Property operator

    template<class T>
    template<AssignOp<T> _T>
    Property<T> &Property<T>::operator=(const _T &_val)
    {
        m_value = _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignOp<T> _T>
    Property<T> &Property<T>::operator=(const Property<_T> &_val)
    {
        m_value = _val.m_value;
        trigger();
        return *this;
    }

    template<class T>
    template<EqOp<T> _T>
    bool Property<T>::operator==(const _T &_val) const
    {
        return m_value == _val;
    }

    template<class T>
    template<NEqOp<T> _T>
    bool Property<T>::operator!=(const _T &_val) const
    {
        return m_value != _val;
    }

    template<class T>
    template<LsOp<T> _T>
    bool Property<T>::operator<(const _T &_val) const
    {
        return m_value < _val;
    }

    template<class T>
    template<GtOp<T> _T>
    bool Property<T>::operator>(const _T &_val) const
    {
        return m_value > _val;
    }

    template<class T>
    template<LsEqOp<T> _T>
    bool Property<T>::operator<=(const _T &_val) const
    {
        return m_value <= _val;
    }

    template<class T>
    template<GtEqOp<T> _T>
    bool Property<T>::operator>=(const _T &_val) const
    {
        return m_value >= _val;
    }

    template<class T>
    template<GlobCompOp<T> _T>
    bool Property<T>::operator<=>(const _T &_val) const
    {
        return m_value <=> _val;
    }

    template<class T>
    template<AddOp<T> _T>
    T Property<T>::operator+(const _T &_val) const
    {
        return m_value + _val;
    }

    template<class T>
    template<SubOp<T> _T>
    T Property<T>::operator-(const _T &_val) const
    {
        return m_value - _val;
    }

    template<class T>
    template<MulOp<T> _T>
    T Property<T>::operator*(const _T &_val) const
    {
        return m_value * _val;
    }

    template<class T>
    template<DivOp<T> _T>
    T Property<T>::operator/(const _T &_val) const
    {
        return m_value / _val;
    }

    template<class T>
    template<ModOp<T> _T>
    T Property<T>::operator%(const _T &_val) const
    {
        return m_value % _val;
    }

    template<class T>
    template<BitAndOp<T> _T>
    T Property<T>::operator&(const _T &_val) const
    {
        return m_value & _val;
    }

    template<class T>
    template<BitOrOp<T> _T>
    T Property<T>::operator|(const _T &_val) const
    {
        return m_value | _val;
    }

    template<class T>
    template<BitXorOp<T> _T>
    T Property<T>::operator^(const _T &_val) const
    {
        return m_value ^ _val;
    }

    template<class T>
    template<LShiftOp<T> _T>
    T Property<T>::operator<<(const _T &_val) const
    {
        return m_value << _val;
    }

    template<class T>
    template<RShiftOp<T> _T>
    T Property<T>::operator>>(const _T &_val) const
    {
        return m_value >> _val;
    }

    template<class T>
    template<AssignAddOp<T> _T>
    Property<T> Property<T>::operator+=(const _T &_val)
    {
        m_value += _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignSubOp<T> _T>
    Property<T> Property<T>::operator-=(const _T &_val)
    {
        m_value -= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignMulOp<T> _T>
    Property<T> Property<T>::operator*=(const _T &_val)
    {
        m_value *= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignDivOp<T> _T>
    Property<T> Property<T>::operator/=(const _T &_val)
    {
        m_value /= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignModOp<T> _T>
    Property<T> Property<T>::operator%=(const _T &_val)
    {
        m_value %= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignBitAndOp<T> _T>
    Property<T> Property<T>::operator&=(const _T &_val)
    {
        m_value &= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignBitOrOp<T> _T>
    Property<T> Property<T>::operator|=(const _T &_val)
    {
        m_value |= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignBitXorOp<T> _T>
    Property<T> Property<T>::operator^=(const _T &_val)
    {
        m_value ^= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignLShiftOp<T> _T>
    Property<T> Property<T>::operator<<=(const _T &_val)
    {
        m_value <<= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignRShiftOp<T> _T>
    Property<T> Property<T>::operator>>=(const _T &_val)
    {
        m_value >>= _val;
        trigger();
        return *this;
    }

    // template<class T>
    // requires PreIncOp<T>
    // Property<T> Property<T>::operator++()
    // {
    //     m_value++;
    //     return *this;
    // }

    // template<class T>
    // requires PostIncOp<T>
    // Property<T> Property<T>::operator++(int)
    // {
    //     ++m_value;
    //     return *this;
    // }

    // template<class T>
    // requires PreDecOp<T>
    // Property<T> Property<T>::operator--()
    // {
    //     m_value--;
    //     return *this;
    // }

    // template<class T>
    // requires PostDecOp<T>
    // Property<T> Property<T>::operator--(int)
    // {
    //     --m_value;
    //     return *this;
    // }

#pragma endregion
}