#include "ECS/System/RenderModel.hpp"

#include <iostream>
#include <algorithm>

namespace ecs::sys
{
    void RenderModel::run(MainRegister &_reg, Entity *_entity, eng::Window *_window)
    {
        std::ignore = _entity;

        for (auto &[_key, _val] : _reg)
            if (opt::get<ecs::comp::Model>(_val).has_value())
                _window->drawModel(opt::get<ecs::comp::Model>(_val).value().mod);
                // process(opt::get<ecs::comp::Model>(_val).value(), _window);
    }

    // void RenderModel::process(ecs::comp::Model &_model, eng::Window *_window) const
    // {
    //     std::vector<eng::Point2<float>> projection = transform(_model, _window);
    //     const std::vector<eng::Point3<float>>& txtrPt = _model.mod.getTexturePoint();
    //     std::vector<sf::VertexArray> vertexs;

    //     for (const auto &_poly : _model.mod.getPoly()) {
    //         sf::VertexArray vertex(sf::TriangleStrip, 3);

    //         for (size_t it = 0; it < _poly.size(); it++) {
    //             if (_poly.at(it).x > 0)
    //                 vertex[it].position = projection[_poly.at(it).x - 1];
    //             else
    //                 vertex[it].position = projection[projection.size() + _poly.at(it).x];
    //             if (_poly.at(it).y > 0)
    //                 vertex[it].texCoords = { txtrPt[_poly.at(it).y - 1].x, txtrPt[_poly.at(it).y - 1].y };
    //             else if (_poly.at(it).y < 0)
    //                 vertex[it].texCoords = { txtrPt[txtrPt.size() + _poly.at(it).y].x, txtrPt[txtrPt.size() + _poly.at(it).y].y };
    //         }
    //         vertexs.emplace_back(vertex);
    //     }
    //     for (auto& _draw : vertexs)
    //         _window->draw(_draw, _model.mod.getTexture().get());
    // }

    // std::vector<eng::Point2<float>> RenderModel::transform(const ecs::comp::Model &_model, eng::Window *_window) const
    // {
    //     std::vector<eng::Point2<float>> vertex;

    //     for (const auto &_pt : _model.mod.getPoint())
    //         vertex.push_back(_window->project(_pt));
    //     return vertex;
    // }
}