#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

#include "XML/Tokenizer.hpp"

namespace eng::xml
{
    std::vector<Token> Tokenizer::run(const std::string &_file)
    {
        std::ifstream file(_file);

        if (!file.is_open())
            throw std::runtime_error("error");
        return run(file);
    }

    std::vector<Token> Tokenizer::run(std::istream &_stream)
    {
        std::vector<Token> ltoken;
        Token token;
        bool readed = false;

        while (goNextToken(_stream)) {
            for (const auto &_fn : m_readfn) {
                readed = _fn(_stream, token);
                if (readed)
                    break;
                token.value.clear();
            }
            if (!readed && !_stream.eof())
                throw std::runtime_error("error");
            ltoken.push_back(token);
            token.value.clear();
        }
        return ltoken;
    }

    bool Tokenizer::readLWord(std::istream &_stream, Token &_token)
    {
        size_t cursor = _stream.tellg();
        char get = 0;

        _token.type = Token::Type::LWord;
        _stream.get(get);
        if (get != '"') {
            _stream.seekg(cursor);
            return false;
        }
        std::getline(_stream, _token.value, '"');
        _stream.seekg(_stream.tellg() - 1ll);
        _stream.get(get);
        if (get != '"') {
            _stream.seekg(cursor);
            return false;
        }
        return true;
    }

    bool Tokenizer::readWord(std::istream &_stream, Token &_token)
    {
        int64_t cursor = _stream.tellg();
        char get = 0;
        const std::string skip("abcdefghijklmnopqrstuvwxyzABCDERFGHIJKLMNOPQRSTUVWXYZ");

        _token.type = Token::Type::Word;
        _stream.get(get);
        _stream.seekg(cursor);
        if (skip.find(get) == std::string::npos)
            return false;
        while (!_stream.eof()) {
            _stream.get(get);
            if (get == 0) {
                _stream.seekg(cursor == -1 ? 0 : cursor);
                return false;
            }
            if (skip.find(get) == std::string::npos) {
                _stream.seekg(_stream.tellg() - 1ll);
                return true;
            }
            _token.value += get;
        }
        _stream.seekg(cursor);
        return false;
    }

    bool Tokenizer::readOpenBalise(std::istream &_stream, Token &_token)
    {
        _token.type = Token::Type::Open;
        _token.value = "<";
        return isSingleToken(_stream, _token);
    }

    bool Tokenizer::readCloseBalise(std::istream &_stream, Token &_token)
    {
        _token.type = Token::Type::Close;
        _token.value = ">";
        return isSingleToken(_stream, _token);
    }

    bool Tokenizer::readCloseSign(std::istream &_stream, Token &_token)
    {
        _token.type = Token::Type::CloseSign;
        _token.value = "/";
        return isSingleToken(_stream, _token);
    }

    bool Tokenizer::readEqual(std::istream &_stream, Token &_token)
    {
        _token.type = Token::Type::Equal;
        _token.value = "=";
        return isSingleToken(_stream, _token);
    }

    bool Tokenizer::goNextToken(std::istream &_stream)
    {
        char get = 0;
        const std::string skip(" \t\n\r");
        int64_t cursor = _stream.tellg();

        while (!_stream.eof()) {
            _stream.get(get);
            if (get == 0)
                break;
            if (skip.find(get) == std::string::npos) {
                _stream.seekg(_stream.tellg() - 1ll);
                return true;
            }
        }
        _stream.seekg(cursor == -1 ? 0 : cursor);
        return false;
    }

    bool Tokenizer::isSingleToken(std::istream &_stream, const Token &_token)
    {
        size_t cursor = _stream.tellg();
        char get = 0;

        _stream.get(get);
        if (get == _token.value[0])
            return true;
        _stream.seekg(cursor);
         return false;
    }
}