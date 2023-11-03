#pragma once

#include <string>
#include <vector>
#include <map>

#include "Tool/Export.hpp"

namespace eng::xml
{
    using Value = std::pair<std::string, std::string>;

    class PROJECT_API Balise
    {
        public:
            enum Type
            {
                Single,
                Children,
                NoSub
            };

            Balise() = default;
            ~Balise() = default;

            void setName(const std::string &_name);
            void setType(Type _type);
            void addValue(const Value &_value);
            void addChildren(const Balise &_balise);
            void setContent(const std::string &_data);

            [[nodiscard]] Type getType() const;
            [[nodiscard]] std::string &getName();
            [[nodiscard]] std::vector<Balise> &getChild();
            [[nodiscard]] std::string &getContent();

            std::string &operator[](const std::string &_id);

            PROJECT_API friend std::ostream &operator<<(std::ostream &_os, const Balise &_balise);

        protected:
            static std::ostream &writeBalise(std::ostream &_os, const Balise &_balise, size_t _it = 0);

        private:
            std::map<std::string, std::string> m_value;
            std::vector<Balise> m_child;
            std::string m_content;
            Type m_type;
            std::string m_name;
    };
}