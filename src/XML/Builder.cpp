#include "XML/Builder.hpp"

namespace eng::xml
{
    Balise Builder::run(const std::vector<Token> &_token)
    {
        size_t it = 0;

        return run(_token, it);
    }

    Balise Builder::run(const std::string &_file)
    {
        size_t it = 0;

        return run(Tokenizer::run(_file), it);
    }

    Balise Builder::run(const std::vector<Token> &_token, size_t &_it)
    {
        Balise balise;

        if (_token[_it].type == Token::Type::Open && _token[++_it].type == Token::Type::Word) {
            balise.setName(_token[_it].value);
            _it++;
            while (_token[_it].type != Token::Type::CloseSign && _token[_it].type != Token::Type::Close) {
                if (_token[_it].type != Token::Type::Word) {
                    throw std::runtime_error("error: should parse word for value");
                } else if (_token[_it + 1].type == Token::Type::Equal) {
                    throw std::runtime_error("error: should parse equal for value");
                } else if (_token[_it + 2].type  == Token::Type::LWord) {
                    throw std::runtime_error("error: should parse lword for value");
                }
                balise.addValue({ _token[_it].value, _token[_it + 2].value });
                _it += 3;
            }
            if (_token[_it].type == Token::Type::CloseSign) {
                if (_token[++_it].type != Token::Type::Close)
                    throw std::runtime_error("error: wrong syntax on single balise end");
                balise.setType(Balise::Type::Single);
            } else {
                // content of the balise
                balise.addChildren(run(_token, ++_it));
                balise.setType(Balise::Type::Children);
                if (_token[_it].type != Token::Type::Open || _token[_it + 1].type != Token::Type::CloseSign &&
                    _token[_it + 2].type != Token::Type::Word && balise.getName() != _token[_it + 2].value &&
                    _token[_it + 3].type != Token::Type::Close)
                    throw std::runtime_error("error: no end balise for non Single balise");
            }
            return balise;
        }
        throw std::runtime_error("error: this element isn't a baliser");
    }
}