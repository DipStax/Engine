#pragma once

#include "XML/UI/EventObject.hpp"
#include "Engine/Event/Property.hpp"

namespace eng::ui
{
    template<class ...Ts>
    class PropertyObject : public EventObject<Ts...>
    {
        public:
            PropertyObject(ThreadPool &_tp);
            PropertyObject(PropertyObject<Ts...> &&_obj) noexcept;
            ~PropertyObject() = default;

        protected:
            template<class T>
            using fn_conv = std::function<T (const std::string &)>;
            using fn_assign = std::function<void (const std::string &)>;

            // add more buildin convertion
            [[nodiscard]] Property<std::string>::PropTrigger::sTask registerProperty(Property<std::string> &_prop);
            template<IsUnsigned T>
            [[nodiscard]] Property<T>::PropTrigger::sTask registerProperty(Property<T> &_prop);
            template<IsSigned T>
            [[nodiscard]] Property<T>::PropTrigger::sTask registerProperty(Property<T> &_prop);
            template<IsFPN T>
            [[nodiscard]] Property<T>::PropTrigger::sTask registerProperty(Property<T> &_prop);

            template<class T>
            [[nodiscard]] Property<T>::PropTrigger::sTask registerProperty(Property<T> &_prop, fn_conv<T> _conv);

            template<class T>
            requires ContainIn<typename Property<T>::Event, Ts...>
            void unregisterProperty(Property<T>::PropTrigger::sTask _stask);

            void setProperty(const std::string &_name, const std::string &_val);

            template<class T>
            required !ContainIn<T, Ts...>;
            [[nodiscard]] constexpr bool acceptEvent(const T &_event) const noexcept;

            template<class T>
            requires ContainIn<T, Ts...>;
            [[nodiscard]] constexpr bool acceptEvent(const T &_event) const noexcept;

            template<class T>
            void handleEvent(const T &_event) = delete;

            template<class T>
            requires ContainIn<T, Ts...>;
            virtual void handleEvent(const T &_event) = 0;

        private:
            template<class T>
            [[nodiscard]] Property<T>::PropTrigger::sTask bindProperty(Property<T> &_prop);

            std::unordered_map<std::string, fn_assign> m_conv;
    };
}

#include "XML/UI/PropertyObject.inl"