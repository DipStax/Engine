#pragma once

#include <istream>
#include <vector>

#include "XML/Token.hpp"

namespace eng::xml
{
    class PROJECT_API Tokenizer
    {
        public:
            static [[nodiscard]] std::vector<Token> run(const std::string &file);
            static [[nodiscard]] std::vector<Token> run(std::istream &_stream);

        protected:
            static [[nodiscard]] bool readLWord(std::istream &_stream, Token &_token);
            static [[nodiscard]] bool readWord(std::istream &_stream, Token &_token);
            static [[nodiscard]] bool readOpenBalise(std::istream &_stream, Token &_token);
            static [[nodiscard]] bool readCloseBalise(std::istream &_stream, Token &_token);
            static [[nodiscard]] bool readCloseSign(std::istream &_stream, Token &_token);
            static [[nodiscard]] bool readEqual(std::istream &_stream, Token &_token);
            static bool goNextToken(std::istream &_stream);

        private:
            static bool isSingleToken(std::istream &_stream, const Token &_token);

            using readFn = bool (*)(std::istream &, Token &_token);

            inline static const std::vector<readFn> m_readfn{
                &Tokenizer::readLWord,
                &Tokenizer::readWord,
                &Tokenizer::readOpenBalise,
                &Tokenizer::readCloseBalise,
                &Tokenizer::readCloseSign,
                &Tokenizer::readEqual
            };
    };
}