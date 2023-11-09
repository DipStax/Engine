#pragma once

#define OBJECT_EVENT Property<uint32_t>::Event

#include "Tool/PreProcessing.hpp"
#include "XML/UI/ObjectRegistre.hpp"
#include "XML/UI/PropertyObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    using ObjectEvent = typename unique_type<OBJECT_EVENT, Ts...>::type;

    template<class ...Ts>
    class Object;

    template<class ...Ts>
    class Object<std::tuple<Ts...>> : public BaseObject, public PropertyObject<ObjectEvent<Ts...>>
    {
        public:
            Object(const std::string &_type, ThreadPool &_tp);
            Object(Object &&_obj) noexcept;
            ~Object();

            Property<uint32_t> Width;
            Property<uint32_t> Height;
            [[nodiscard]] Point2<uint32_t> getSize() const;

            // virtual acceptor implementation

        private:
            void ownProperty();

            PropertyBind<uint32_t> m_bind_width;
            PropertyBind<uint32_t> m_inter_width;
            PropertyBind<uint32_t> m_bind_height;
            PropertyBind<uint32_t> m_inter_height;
    };
}

#include "XML/UI/Object.inl"