#pragma once

#include "Engine/Event/Property.hpp"



namespace eng
{
    namespace Factory
    {
        class Balise;
    }

    namespace ui
    {
        class PropertyRegistre
        {
            public:
                PropertyRegistre() = default;
                ~PropertyRegistre() = default;

            protected:
                template<class T>
                using fn_conv = std::function<T (const std::string &)>;
                using fn_assign = std::function<void (const std::string &)>;

                [[nodiscard]] void registerProperty(Property<std::string> &_prop);
                template<IsUnsigned T>
                [[nodiscard]] void registerProperty(Property<T> &_prop);
                template<IsSigned T>
                [[nodiscard]] void registerProperty(Property<T> &_prop);
                template<IsFPN T>
                [[nodiscard]] void registerProperty(Property<T> &_prop);

                template<class T>
                [[nodiscard]] void registerProperty(Property<T> &_prop, fn_conv<T> _conv);

                friend class Factory::Balise;

                void setProperty(const std::string &_name, const std::string &_val);

            private:
                std::unordered_map<std::string, fn_assign> m_conv{};
        };
    }
}