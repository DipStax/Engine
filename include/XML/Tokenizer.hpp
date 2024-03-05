#pragma once

#include <istream>
#include <vector>

#include "XML/Token.hpp"

namespace eng::xml
{
    class PROJECT_API Tokenizer
    {
        public:
            [[nodiscard]] static std::vector<Token> run(const std::string &file);
            [[nodiscard]] static std::vector<Token> run(std::istream &_stream);

        protected:
            [[nodiscard]] static bool readLWord(std::istream &_stream, Token &_token);
            [[nodiscard]] static bool readWord(std::istream &_stream, Token &_token);
            [[nodiscard]] static bool readOpenBalise(std::istream &_stream, Token &_token);
            [[nodiscard]] static bool readCloseBalise(std::istream &_stream, Token &_token);
            [[nodiscard]] static bool readCloseSign(std::istream &_stream, Token &_token);
            [[nodiscard]] static bool readEqual(std::istream &_stream, Token &_token);
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