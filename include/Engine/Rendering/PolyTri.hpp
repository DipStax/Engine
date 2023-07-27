#pragma once

#include <array>
#include <vector>

#include "Engine/Container/CircleList.hpp"
#include "Engine/Rendering/Vertex.hpp"

namespace eng
{
    std::vector<std::array<Vertex, 3>> polyTri(const Vertex *_vtx, size_t _size);
    Point2<uint32_t> triRange(const Vertex *_vtx, int32_t _line);
    Point2<uint32_t> triRange(const Vertex3D* _vtx, int32_t _line);

    namespace priv
    {
        bool isEarTip(const CircleList<Vertex> &_cl, size_t _start);
        float calInside(const Point2<float> &_pt, const Point2<float>& _a, const Point2<float> &_b, const Point2<float>& _c);
        bool reflex(const Point2<float> _prev, const Point2<float> &_cur, const Point2<float> &_next);
    }
}