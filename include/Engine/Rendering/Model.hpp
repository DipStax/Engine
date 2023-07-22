#ifndef ENG_RSC_MODEL_HPP
#define ENG_RSC_MODEL_HPP

#include <istream>
#include <map>
#include <string>
#include <vector>

#include "Engine/Rendering/Texture.hpp"
#include "Engine/Rendering/Vertex.hpp"
#include "Engine/Camera.hpp"

namespace eng
{
    class Model
    {
        public:
            Model();
            ~Model() = default;
            Model &operator=(const Model &_model);

            Model copy() const;

            void load(const std::string &_path);

            [[nodiscard]] size_t getTextureId() const;
            [[nodiscard]] std::shared_ptr<Texture> getTexture() const;

            void setTextureId(size_t _id);
            void setTexture(std::shared_ptr<Texture> _txtr);

            [[nodiscard]] const std::vector<eng::Vector3<float>> &getPoint() const;
            [[nodiscard]] const std::vector<eng::Vector3<float>> &getTexturePoint() const;
            [[nodiscard]] const std::vector<std::vector<eng::Point3<int64_t>>> &getPoly() const;

        protected:
            using FnParsing = void (Model::*)(const std::string &);

            static void Init();
            static inline std::map<std::string, FnParsing> m_fnParsing;

            // https://en.wikipedia.org/wiki/Wavefront_.obj_file
            void fnLoadF(const std::string &_file);
            void fnLoadV(const std::string &_file);
            void fnLoadVn(const std::string &_file);
            void fnLoadVp(const std::string &_file);
            void fnLoadVt(const std::string &_file);
            void fnComment(const std::string &_file);

        private:
            std::vector<eng::Vector3<float>> m_v;
            std::vector<eng::Vector3<float>> m_vn;
            std::vector<eng::Vector3<float>> m_vt;
            std::vector<eng::Vector3<float>> m_vp;
            std::vector<std::vector<eng::Point3<int64_t>>> m_f;

            std::shared_ptr<Texture> m_txtr = nullptr;
            size_t m_txtrId = 0;

            std::vector<Vertex> m_varray;
    };
}

#endif