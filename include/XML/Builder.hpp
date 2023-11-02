#pragma once

#include "XML/Balise.hpp"
#include "XML/Tokenizer.hpp"

namespace eng::xml
{
    class PROJECT_API Builder
    {
        public:
            static Balise run(const std::vector<Token> &_token);
            static Balise run(const std::string &_file);

        private:
            static Balise run(const std::vector<Token> &_token, size_t &_it);
    };
}