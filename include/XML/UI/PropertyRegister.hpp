#pragma once

#include "Engine/Event/Property.hpp"
#include "Tool/Export.hpp"

namespace eng
{
    namespace Factory
    {
        class Balise;
    }

    namespace ui
    {
        class PROJECT_API PropertyRegister
        {
            public:
                PropertyRegister() = default;
                ~PropertyRegister() = default;

            protected:
                template<class T>
                using fn_conv = std::function<T (const std::string &)>;
                using fn_assign = std::function<void (const std::string &)>;

                void registerProperty(Property<std::string> &_prop);
                template<IsUnsigned T>
                void registerProperty(Property<T> &_prop);
                template<IsSigned T>
                void registerProperty(Property<T> &_prop);
                template<IsFPN T>
                void registerProperty(Property<T> &_prop);

                template<class T>
                void registerProperty(Property<T> &_prop, fn_conv<T> _conv);

                friend class Factory::Balise;

                void setProperty(const std::string &_name, const std::string &_val);

            private:
                std::unordered_map<std::string, fn_assign> m_conv{};
        };
    }
}

#include "XML/UI/PropertyRegister.inl"