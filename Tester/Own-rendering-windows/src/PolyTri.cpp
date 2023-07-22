#include "PolyTri.hpp"
#include "Engine/Area.hpp"

namespace tester
{
    std::vector<std::array<Vertex, 3>> polyTri(const Vertex *_vtx, size_t _size)
    {
        std::vector<std::array<Vertex, 3>> res;
        CircleList<Vertex> cl;

        for (int32_t it = 0; it < _size; it++)
            cl.push_back(_vtx[it]);
        for (int32_t it = 0; cl.size() != 3;) {
            if (priv::isEarTip(cl, it)) {
                res.push_back({ cl[it - 1], cl[it], cl[it + 1] });
                cl.erase(it);
            } else {
                it++;
            }
        }
        res.push_back({ cl[0], cl[1], cl[2] });
        return res;
    }

    namespace priv
    {
        bool isEarTip(const CircleList<Vertex> &_cl, size_t _start)
        {
            int32_t start = static_cast<int32_t>(_start);
            float size = area(_cl[start - 1].pos, _cl[start].pos, _cl[start + 1].pos);
            float inside = 0;

            if (reflex(_cl[start - 1].pos, _cl[start].pos, _cl[start + 1].pos))
                return false;
            for (int32_t it = start + 2; it < start + _cl.size() - 2; it++) {
                inside = calInside(_cl[it].pos, _cl[start - 1].pos, _cl[start].pos, _cl[start + 1].pos);
                if (size - 1 < inside && inside < size + 1)
                    return false;
            }
            return true;
        }

        float calInside(const Point2<float> &_pt, const Point2<float>& _a, const Point2<float> &_b, const Point2<float>& _c)
        {
            return area(_pt, _b, _c) + area(_a, _pt, _c) + area(_a, _b, _pt);
        };

        bool reflex(const Point2<float> _prev, const Point2<float> &_cur, const Point2<float> &_next)
        {
            Point2<float> cp = _cur - _prev;
            Point2<float> nc = _next - _cur;

            return (cp.x * nc.y - cp.y * nc.x) < 0;
        }
    }
}

