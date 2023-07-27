#include <fstream>
#include <iostream>

#include "Tool/Splitter.hpp"
#include "Engine/Rendering/Model.hpp"
#include "Engine/Rendering/RenderTarget3D.hpp"

namespace eng
{
    Model::Model()
    {
        Init();
    }

    Model &Model::operator=(const Model &_model)
    {
        if (this == &_model)
            return *this;
        m_v = _model.m_v;
        m_vn = _model.m_vn;
        m_vt = _model.m_vt;
        m_vp = _model.m_vp;
        m_vp = _model.m_vp;
        m_f = _model.m_f;
        m_txtr = _model.m_txtr;
        m_txtrId = _model.m_txtrId;
        return *this;
    }

    Model Model::copy() const
    {
        Model model = *this;

        return std::move(model);
    }

    void Model::load(const std::string &_path)
    {
        std::ifstream file;
        std::string line;
        std::pair<std::string, std::string> pair;

        std::cout << "[rsc::Model] load - start" << std::endl;
        file.open(_path);
        while (std::getline(file, line)) {
            pair = split::noSpace(line, ' ');
            if (m_fnParsing.contains(pair.first)) {
                try {
                    (this->*(m_fnParsing[pair.first]))(line);
                } catch (std::exception &_excp) {
                    throw std::runtime_error("[Mdoel](" + _path + "): Internal error: " + _excp.what() + " | '" + line + "'");
                }
            }
            else if (!line.empty() && line.at(0) == '#') {
                fnComment("");
            } else if (!line.empty()) {
                throw std::runtime_error("[Mdoel](" + _path + "): Unknow flag: '" + line + "'");
            }
        }
        std::cout << "[rsc::Model] load - done" << std::endl;
    }

    void Model::setTextureId(size_t _id)
    {
        m_txtrId = _id;
    }

    size_t Model::getTextureId() const
    {
        return m_txtrId;
    }

    void Model::setTexture(std::shared_ptr<Texture> _txtr)
    {
        m_txtr = _txtr;
    }

    std::shared_ptr<Texture> Model::getTexture() const
    {
        return m_txtr;
    }

    void Model::draw(RenderTarget3D &_target, const Texture *_txtr) const
    {
        std::ignore = _txtr;

        for (const auto &_f : m_f)
            _target.draw(_f.data(), _f.size(),  m_txtr.get());
    }

    void Model::Init()
    {
        static bool init = false;

        if (init)
            return;
        init = true;
        m_fnParsing["f"] = &Model::fnLoadF;
        m_fnParsing["v"] = &Model::fnLoadV;
        m_fnParsing["vn"] = &Model::fnLoadVn;
        m_fnParsing["vp"] = &Model::fnLoadVp;
        m_fnParsing["vt"] = &Model::fnLoadVt;
        m_fnParsing["#"] = &Model::fnComment;
    }

    void Model::fnLoadF(const std::string &_line)
    {
        std::vector<std::string> multi = split::multiple(_line, ' ', true);
        std::vector<std::string> param;
        std::vector<Vertex3D> f;

        multi.erase(multi.begin());
        if (multi.size() < 3)
            throw std::runtime_error("Not enough parameters");
        for (auto &_pt : multi) {
            Vertex3D vtx;

            param = split::multiple(_pt, '/', false);
            if (param.size() < 1 || param.size() > 3)
                throw std::runtime_error("not enough value in the parameters");
            vtx.pos = m_v[std::stoll(param.at(0)) - 1];
            if (param.size() > 1) {
                if (!param.at(1).empty())
                    vtx.txtrPos = m_vt[std::stoll(param.at(1)) - 1].as2();
                // if (param.size() > 2)
                // handling normalized vector ?
            }
            f.push_back(vtx);
        }
        std::cout << "f loaded: " << m_f.size() << std::endl;
        m_f.push_back(f);
    }

    void Model::fnLoadV(const std::string &_line)
    {
        std::pair<std::string, std::string> pair = split::noSpace(_line, '#');
        std::vector<std::string> multi = split::multiple(pair.first, ' ', true);

        m_v.push_back({ std::stof(multi.at(1)), std::stof(multi.at(2)), std::stof(multi.at(3)) });
    }

    void Model::fnLoadVn(const std::string &_line)
    {
        std::pair<std::string, std::string> pair = split::noSpace(_line, '#');
        std::vector<std::string> multi = split::multiple(_line, ' ', true);

        m_vn.push_back({ std::stof(multi.at(1)), std::stof(multi.at(2)), std::stof(multi.at(3)) });
    }

    void Model::fnLoadVt(const std::string &_line)
    {
        std::pair<std::string, std::string> pair = split::noSpace(_line, '#');
        std::vector<std::string> multi = split::multiple(_line, ' ', true);
        Vector3<float> vec;

        multi.erase(multi.begin());
        vec.x = std::stof(multi.at(0));
        vec.y = (multi.size() > 1) ? std::stof(multi.at(1)) : 0;
        vec.z = (multi.size() > 2) ? std::stof(multi.at(2)) : 0;
        if (vec.y < 0 || vec.y > 1 || vec.z < 0 || vec.z > 1)
            throw std::runtime_error("Optional parameter doesn't fit");
        m_vt.push_back(vec);
    }

    void Model::fnLoadVp(const std::string &_line)
    {
        std::pair<std::string, std::string> pair = split::noSpace(_line, '#');
        std::vector<std::string> multi = split::multiple(_line, ' ', true);
        Vector3<float> vec;

        vec.x = std::stof(multi.at(1));
        vec.y = (multi.size() > 1) ? 0 : std::stof(multi.at(2));
        vec.z = (multi.size() > 2) ? 0 : std::stof(multi.at(2));
        m_v.push_back(vec);
    }

    void Model::fnComment(const std::string &_line)
    {
        std::ignore = _line;
    }
}