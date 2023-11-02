#pragma once

#include <string>
#include <vector>
#include <memory>

namespace eng::ui
{
    class BaseObject;

    class ObjectRegistre
    {
        public:
            ObjectRegistre(const std::string &_type);
            ObjectRegistre(ObjectRegistre &&_obj) noexcept;
            ~ObjectRegistre() = default;

            [[nodiscard]] const std::string &getType() const;

        protected:
            void addContent(std::shared_ptr<BaseObject> _obj);

            // virtual pure acceptor

        private:
            std::vector<std::shared_ptr<BaseObject>> m_content{};

            const std::string m_type;
    };
}