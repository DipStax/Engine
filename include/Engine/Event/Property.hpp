#pragma once

#include <string_view>
#include <tuple>

#include "Engine/Event/EventPool.hpp"
#include "Engine/Event/PropertyEvent.hpp"
#include "Tool/PreProcessing.hpp"

namespace eng
{
    template<class T>
    class Property
    {
        public:
            template<class ...Ts>
            Property(EventPool<PropertyEvent> &_ep, std::string_view &_name, Ts &&..._args);
            Property(const Property &_prop) = delete;
            ~Property() = default;

            void trigger();

            [[nodiscard]] const std::string &getName() const;

            template<AssignOp _T>
            Property<T> &operator=(const _T &_val);
            template<AssignOp _T>
            Property<T> &operator=(const Property<_T> &_val);

            operator T&();
            explicit operator T() const;

            // need to return a template value?
            template<EqOp _T>
            [[nodiscard]] bool operator==(const _T &_val) const;
            template<NEqOp _T>
            [[nodiscard]] bool operator!=(const _T &_val) const;
            template<LsOp _T>
            [[nodiscard]] bool operator<(const _T &_val) const;
            template<GtOp _T>
            [[nodiscard]] bool operator>(const _T &_val) const;
            template<LsEqOp _T>
            [[nodiscard]] bool operator<=(const _T &_val) const;
            template<GtEqOp _T>
            [[nodiscard]] bool operator>=(const _T &_val) const;
            template<GlobCompOp _T>
            [[nodiscard]] bool operator<=>(const _T &_val) const;

            template<AddOp _T>
            [[nodiscard]] T operator+(const _T &_val) const;
            template<SubOp _T>
            [[nodiscard]] T operator-(const _T &_val) const;
            template<MulOp _T>
            [[nodiscard]] T operator*(const _T &_val) const;
            template<DivOp _T>
            [[nodiscard]] T operator/(const _T &_val) const;
            template<ModOp _T>
            [[nodiscard]] T operator%(const _T &_val) const;
            template<BitAndOp _T>
            [[nodiscard]] T operator&(const _T &_val) const;
            template<BitOrOp _T>
            [[nodiscard]] T operator|(const _T &_val) const;
            template<BitXorOp _T>
            [[nodiscard]] T operator^(const _T &_val) const;
            template<LShiftOp _T>
            [[nodiscard]] T operator<<(const _T &_val) const;
            template<RShiftOp _T>
            [[nodiscard]] T operator>>(const _T &_val) const;

            template<AssignAddOp _T>
            Property<T> operator+=(const _T &_val);
            template<AssignSubOp _T>
            Property<T> operator-=(const _T &_val);
            template<AssignMulOp _T>
            Property<T> operator*=(const _T &_val);
            template<AssignDivOp _T>
            Property<T> operator/=(const _T &_val);
            template<AssignModOp _T>
            Property<T> operator%=(const _T &_val);
            template<AssignBitAndOp _T>
            Property<T> operator&=(const _T &_val);
            template<AssignBitOrOp _T>
            Property<T> operator|=(const _T &_val);
            template<AssignBitXorOp _T>
            Property<T> operator^=(const _T &_val);
            template<AssignLShiftOp _T>
            Property<T> operator<<=(const _T &_val);
            template<AssignRShiftOp _T>
            Property<T> operator>>=(const _T &_val);

            template<PreIncOp _T>
            T operator++();
            template<PostIncOp _T>
            Property<T> operator++(int);
            template<PreDecOp _T>
            T operator--();
            template<PostDecOp _T>
            Property<T> operator--(int);

        private:
            const std::string m_name;
            EventPool<PropertyEvent> &m_ep;

            T m_value;
    };
}

#include "Engine/Event/Property.inl"