#include <iostream>
#include <sstream>

#include "Core.hpp"
#include "XML/Builder.hpp"

Core::Core()
{
}

void Core::init(const std::string &_path)
{
    std::istringstream stream("<SimpleBalise value=\"Test LWord\">\
                                   <OtherBalise />\
                                   <Balise val=\"test value\">\
                                       <Single key=\"long value aa \" />\
                                   </Balise>\
                               </Simple Balise>");
    eng::xml::Balise balise;

    auto token = eng::xml::Tokenizer::run(stream);
    for (auto &_token : token)
        std::cout << "Token: " << static_cast<uint16_t>(_token.type) << ", '" << _token.value << "'" << std::endl;
    balise = eng::xml::Builder::run(token);
    std::cout << balise;
}

void Core::run()
{

}