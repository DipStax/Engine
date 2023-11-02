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
            Balise() = default;
            ~Balise() = default;

            void setType(const std::string &_type);
            void addValue(const Value &_value);
            void addChildren(const Balise &_balise);

            [[nodiscard]] std::string &getType();
            [[nodiscard]] const std::string &getType() const;

            [[nodiscard]] std::vector<Balise> &getChild();
            [[nodiscard]] const std::vector<Balise> &getChild() const;

            [[nodiscard]] std::map<std::string, std::string> &getValue();
            [[nodiscard]] const std::map<std::string, std::string> &getValue() const;

            std::string &operator[](const std::string &_name);

            PROJECT_API friend std::ostream &operator<<(std::ostream &_os, const Balise &_balise);

        protected:
            static std::ostream &writeBalise(std::ostream &_os, const Balise &_balise, size_t _it = 0);

        private:
            std::map<std::string, std::string> m_value;
            std::vector<Balise> m_child;
            std::string m_type;
    };
}