#ifndef ENG_RSC_LOADER_HPP
#define ENG_RSC_LOADER_HPP

#include <istream>
#include <memory>

#include "Engine/Rendering/Data.hpp"

namespace eng
{
    class Loader
    {
        public:
            Loader() = default;
            ~Loader() = default;

            [[nodiscard]] Data load(const std::string &_path);

            [[nodiscard]] std::pair<size_t, std::shared_ptr<Texture>> loadTexture(std::istream &_file);
            [[nodiscard]] std::pair<size_t, std::unique_ptr<Model>> loadModel(std::istream &_file);

        private:
            using FnLoad = void (Loader::*)(Data &, std::istream &);

            void fnLoadTexture(Data &_data, std::istream &_file);
            void fnLoadModel(Data &_data, std::istream &_file);
    };
}

#endif