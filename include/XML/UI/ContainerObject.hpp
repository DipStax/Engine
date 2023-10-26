#pragma once

#include <string>
#include <vector>
#include <memory>

namespace eng::ui
{
    class ContainerObject
    {
        public:
            ContainerObject(const std::string &_type);
            ContainerObject(ContainerObject &&_obj) noexcept;
            ~ContainerObject() = default;


            [[nodiscard]] const std::string &getType() const;

            [[nodiscard]] bool have(const std::string &_class) const;
            [[nodiscard]] ContainerObject &operator[](const std::string &_class);
            [[nodiscard]] const ContainerObject &operator[](const std::string &_class) const;

        protected:
            void setClass(const std::string &_class);
            [[nodiscard]] const std::string &getClass() const;

            void addContent(ContainerObject &&_container);
            void deleteContent(const std::string &_class);

            // virtual pure acceptor

        private:
            std::vector<ContainerObject> m_content{};

            const std::string m_type;
            std::string m_class{};
    };
}