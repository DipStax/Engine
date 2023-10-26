#pragma once

#define PROPERTY_EVENT Ts...

#include "XML/UI/EventObject.hpp"
#include "Engine/Event/Property.hpp"

namespace eng::ui
{
    template<class ...Ts>
    using PropertyEvent = typename unique_type<PROPERTY_EVENT>::type;

    template<class T>
    using PropertyBind = Trigger<typename Property<T>::Event>::sTask;

    template<class ...Ts>
    class PropertyObject;

    template<class ...Ts>
    class PropertyObject<std::tuple<Ts...>> : public EventObject<PropertyEvent<Ts...>>
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
            [[nodiscard]] void registerProperty(Property<std::string> &_prop);
            template<IsUnsigned T>
            [[nodiscard]] void registerProperty(Property<T> &_prop);
            template<IsSigned T>
            [[nodiscard]] void registerProperty(Property<T> &_prop);
            template<IsFPN T>
            [[nodiscard]] void registerProperty(Property<T> &_prop);

            template<class T>
            [[nodiscard]] void registerProperty(Property<T> &_prop, fn_conv<T> _conv);

            template<class T>
            requires ContainIn<typename Property<T>::Event, Ts...>
            [[nodiscard]] PropertyBind<T> bindProperty(Property<T> &_prop);

            template<class T>
            requires ContainIn<typename Property<T>::Event, Ts...>
            void unbindProperty(PropertyBind<T> _stask);

            void setProperty(const std::string &_name, const std::string &_val);

        private:
            std::unordered_map<std::string, fn_assign> m_conv{};
    };
}

#include "XML/UI/PropertyObject.inl"