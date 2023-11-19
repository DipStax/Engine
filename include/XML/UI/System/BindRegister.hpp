#pragma once

#include "Engine/Event/Property.hpp"

#include <functional>

namespace eng::ui
{
    template<class ...Ts>
    class BindRegister
    {
        public:
            public:
                template<class T>
                using fn = std::function<std::shared_ptr<T> (Property<T> &)>;

                BindRegister() = default;
                ~BindRegister();

                template<class T, class ..._Ts>
                requires ContainIn<T, Ts...>
                size_t add(Property<T> &_prop, fn_bind<T> _bind, _Ts &&..._binds);
                template<class T>
                requires ContainIn<T, Ts...>
                size_t add(Property<T> &_prop, fn_bind<T> _bind);
                template<class T>
                requires ContainIn<T, Ts...>
                size_t add(std::shared_ptr<T> _bind);

                template<class T>
                requires ContainIn<T, Ts...>
                [[nodiscard]] std::vector<std::shared_ptr<T>> get() const;

                template<class T>
                requires ContainIn<T, Ts...>
                bool del(std::shared_ptr<T> _bind);

                void clear();
                template<class T, class ..._Ts>
                requires ContainIn<T, Ts...>
                void clear();
                template<class T>
                requires ContainIn<T, Ts...>
                void clear();

        private:
            std::tuple<std::vector<std::shared_ptr<Ts>>...> m_bind;
    };
}