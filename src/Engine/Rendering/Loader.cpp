#include <fstream>
#include <iostream>

#include "Engine/Rendering/Loader.hpp"
#include "Tool/Splitter.hpp"

namespace eng
{
    Data Loader::load(const std::string &_path)
    {
        std::cout << "[rsc::Loader] load - start" << std::endl;
        std::cout << "[rsc::Loader] File: " << _path << std::endl;
        std::ifstream file;
        Data data{};
        std::string line = "";
        FnLoad fn;

        file.open(_path);
        while (std::getline(file, line)) {
            std::cout << "[rsc::Loader] parsing: '" << line << "'" << std::endl;
            if (line == "Texture:")
                fn = &Loader::fnLoadTexture;
            else if (line == "Model:")
                fn = &Loader::fnLoadModel;
            else
                continue;
            while (std::getline(file, line) && !line.empty())
                (this->*fn)(data, file);
        }
        for (auto &_model : data.Model)
            if (_model.second->getTextureId())
                _model.second->setTexture(data.Texture.at(_model.second->getTextureId()));
        return data;
    }

    std::pair<size_t, std::shared_ptr<Texture>> Loader::loadTexture(std::istream &_file)
    {
        std::shared_ptr<Texture> txtr = std::make_shared<Texture>();
        std::string line = "";
        std::pair<std::string, std::string> kv;
        size_t id = 0;

        while (line != "}") {
            std::getline(_file, line);
            kv = split::noSpace(line, ':');
            if (kv.first == "Path") {
                txtr->load(kv.second);
            } else if (kv.first == "Id") {
                id = std::stoull(kv.second);
            } else if (line != "}") {
                return { 0, nullptr };
            }
        }
        return { id, txtr };
    }

    std::pair<size_t, std::unique_ptr<Model>> Loader::loadModel(std::istream& _file)
    {
        std::unique_ptr<Model> model = std::make_unique<Model>();
        std::string line = "";
        std::pair<std::string, std::string> kv;
        size_t id = 0;

        while (line != "}") {
            std::getline(_file, line);
            kv = split::noSpace(line, ':');
            if (kv.first == "Path") {
                model->load(kv.second);
            } else if (kv.first == "Id") {
                id = std::stoull(kv.second);
            } else if (kv.first == "Linked texture") {
                model->setTextureId(std::stoull(kv.second));
            } else if (line != "}") {
                return { 0, nullptr };
            }
        }
        return std::pair<size_t, std::unique_ptr<Model>>(id, std::move(model));
    }

    void Loader::fnLoadTexture(Data &_data, std::istream &_file)
    {
        std::pair<size_t, std::shared_ptr<Texture>> ptxtr;

        ptxtr = loadTexture(_file);
        if (ptxtr.first && ptxtr.second && !_data.Texture.contains(ptxtr.first))
            _data.Texture.emplace(ptxtr);
    }

    void Loader::fnLoadModel(Data &_data, std::istream &_file)
    {
        std::pair<size_t, std::unique_ptr<Model>> pmodel;

        pmodel = loadModel(_file);
        if (pmodel.first && pmodel.second && !_data.Model.contains(pmodel.first)) {
            pmodel.second->setTexture(_data.Texture.at(pmodel.second->getTextureId()));
            _data.Model.emplace(std::move(pmodel));
        }
    }
}