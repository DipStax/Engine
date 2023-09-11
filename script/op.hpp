Concept

template<AssignAddOp _T>
Property<T> Property<T>::operator+=(const _T &_val)
{
    m_value += _val;
    return *this;
}

template<AssignSubOp _T>
Property<T> Property<T>::operator-=(const _T &_val)
{
    m_value -= _val;
    return *this;
}

template<AssignMulOp _T>
Property<T> Property<T>::operator*=(const _T &_val)
{
    m_value *= _val;
    return *this;
}

template<AssignDivOp _T>
Property<T> Property<T>::operator/=(const _T &_val)
{
    m_value /= _val;
    return *this;
}

template<AssignModOp _T>
Property<T> Property<T>::operator%=(const _T &_val)
{
    m_value %= _val;
    return *this;
}

template<AssignBitAndOp _T>
Property<T> Property<T>::operator&=(const _T &_val)
{
    m_value &= _val;
    return *this;
}

template<AssignBitOrOp _T>
Property<T> Property<T>::operator|=(const _T &_val)
{
    m_value |= _val;
    return *this;
}

template<AssignBitXorOp _T>
Property<T> Property<T>::operator^=(const _T &_val)
{
    m_value ^= _val;
    return *this;
}

template<AssignLShiftOp _T>
Property<T> Property<T>::operator<<=(const _T &_val)
{
    m_value <<= _val;
    return *this;
}

template<AssignRShiftOp _T>
Property<T> Property<T>::operator>>=(const _T &_val)
{
    m_value >>= _val;
    return *this;
}

template<PreIncOp _T>
Property<T> Property<T>::operator++()
{
    m_value++;
    return *this;
}

template<PostIncOp _T>
Property<T> Property<T>::operator++(int)
{
    ++m_value;
    return *this;
}
template<PreDecOp _T>
Property<T> Property<T>::operator--()
{
    m_value--;
    return *this;
}

template<PostDecOp _T>
Property<T> Property<T>::operator--(int)
{
    --m_value;
    return *this;
}
