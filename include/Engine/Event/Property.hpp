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
            using PropEventPool = EventPool<PropertyEvent>;
            using PropTrigger = Trigger<PropertyEvent>;

            Property(PropEventPool &_ep, const std::string &_name, T &_val);
            template<class ...Ts>
            Property(PropEventPool &_ep, const std::string &_name, Ts &&..._args);
            Property(const Property &_prop) = delete;
            ~Property() = default;

            [[nodiscard]] PropTrigger::sTask subscribe(PropTrigger::Task _task);
            void unsubscribe(PropTrigger::sTask _task);

            void trigger();


            [[nodiscard]] const std::string &getName() const;

            template<AssignOp<T> _T>
            Property<T> &operator=(const _T &_val);
            template<AssignOp<T> _T>
            Property<T> &operator=(const Property<_T> &_val);

            operator T&();
            explicit operator T() const;

            // need to return a template value?
            template<EqOp<T> _T>
            [[nodiscard]] bool operator==(const _T &_val) const;
            template<NEqOp<T> _T>
            [[nodiscard]] bool operator!=(const _T &_val) const;
            template<LsOp<T> _T>
            [[nodiscard]] bool operator<(const _T &_val) const;
            template<GtOp<T> _T>
            [[nodiscard]] bool operator>(const _T &_val) const;
            template<LsEqOp<T> _T>
            [[nodiscard]] bool operator<=(const _T &_val) const;
            template<GtEqOp<T> _T>
            [[nodiscard]] bool operator>=(const _T &_val) const;
            template<GlobCompOp<T> _T>
            [[nodiscard]] bool operator<=>(const _T &_val) const;

            template<AddOp<T> _T>
            [[nodiscard]] T operator+(const _T &_val) const;
            template<SubOp<T> _T>
            [[nodiscard]] T operator-(const _T &_val) const;
            template<MulOp<T> _T>
            [[nodiscard]] T operator*(const _T &_val) const;
            template<DivOp<T> _T>
            [[nodiscard]] T operator/(const _T &_val) const;
            template<ModOp<T> _T>
            [[nodiscard]] T operator%(const _T &_val) const;
            template<BitAndOp<T> _T>
            [[nodiscard]] T operator&(const _T &_val) const;
            template<BitOrOp<T> _T>
            [[nodiscard]] T operator|(const _T &_val) const;
            template<BitXorOp<T> _T>
            [[nodiscard]] T operator^(const _T &_val) const;
            template<LShiftOp<T> _T>
            [[nodiscard]] T operator<<(const _T &_val) const;
            template<RShiftOp<T> _T>
            [[nodiscard]] T operator>>(const _T &_val) const;

            template<AssignAddOp<T> _T>
            Property<T> operator+=(const _T &_val);
            template<AssignSubOp<T> _T>
            Property<T> operator-=(const _T &_val);
            template<AssignMulOp<T> _T>
            Property<T> operator*=(const _T &_val);
            template<AssignDivOp<T> _T>
            Property<T> operator/=(const _T &_val);
            template<AssignModOp<T> _T>
            Property<T> operator%=(const _T &_val);
            template<AssignBitAndOp<T> _T>
            Property<T> operator&=(const _T &_val);
            template<AssignBitOrOp<T> _T>
            Property<T> operator|=(const _T &_val);
            template<AssignBitXorOp<T> _T>
            Property<T> operator^=(const _T &_val);
            template<AssignLShiftOp<T> _T>
            Property<T> operator<<=(const _T &_val);
            template<AssignRShiftOp<T> _T>
            Property<T> operator>>=(const _T &_val);

            // requires PreIncOp<T>
            // T operator++();
            // requires PostIncOp<T>
            // Property<T> operator++(int);
            // requires PreDecOp<T>
            // T operator--();
            // requires PostDecOp<T>
            // Property<T> operator--(int);

        private:
            const std::string m_name;
            PropEventPool &m_ep;

            T m_value;
    };
}

#include "Engine/Event/Property.inl"