#pragma once

#include <string>
#include <vector>
#include <memory>

#include "XML/UI/PropertyObject.hpp"

namespace eng::ui
{
    using PropObject = PropertyObject<Property<std::string>::Event, Property<uint32_t>::Event>;

    class ContainerObject : public PropObject
    {
        public:
            ContainerObject(const std::string &_type, Vector2<uint32_t> m_size, ThreadPool &_tp);
            ContainerObject(ContainerObject &&_obj) noexcept;
            ~ContainerObject();

            [[nodiscard]] const std::string &getType() const;

            Property<std::string> Class;
            [[nodiscard]] bool have(const std::string &_class) const;
            [[nodiscard]] ContainerObject &operator[](const std::string &_class);
            [[nodiscard]] const ContainerObject &operator[](const std::string &_class) const;

            Property<uint32_t> Height;
            Property<uint32_t> Width;
            [[nodiscard]] Vector2<uint32_t> getSize() const;

            // implementation of visitor for sending event down?

        protected:
            // friend class ui::Factory;

            // maybe move it to public?
            void addContent(ContainerObject &&_container);
            void deleteContent(const std::string &_class);

        private:
            void ownProperty();

            Property<std::string>::PropTrigger::sTask m_bind_class;
            Property<uint32_t>::PropTrigger::sTask m_bind_height;
            Property<uint32_t>::PropTrigger::sTask m_bind_width;

            std::vector<ContainerObject> m_content;

            const std::string m_type;
    };
}