#ifndef _FLR_ICOSPHERE_H
#define _FLR_ICOSPHERE_H

#include "flare_class.h"
#include "mesh.h"
#include "types.h"
#include "vector.h"
#include <algorithm>
#include <cassert>
#include <unordered_map>

namespace flr {
    FLARE_CLASS(IcoSphere), public Mesh {
        using v3   = flr::v3;
        using Edge = flr::Vector2D<flr::u64>;

    public:
        IcoSphere(flr::Mesh base, flr::f64 radius, flr::u64 subdiv) {
            v3 center = {0, 0, 0};

            for(auto vert : base.points()) { center += vert; }

            center /= base.points().size();

            // center = flr::average(base.points());

            for(auto vert : base.points()) { verts.push_back(vert - center); }

            std::vector<flr::Face> new_fcs;
            fcs = std::vector<flr::Face>(base.faces());
            u64 a, b, c;

            for(u64 i = 0; i < subdiv; i++) {

                for(auto face : fcs) {
                    assert(face.vertices().size() == 3);

                    // base_vertex = verts.size() - 1;

                    // for(flr::u64 i = 0; i < face.vertices().size(); i++) {
                    //     // std::cout << "pushing back " << face.vertices()[i
                    //     %
                    //     // 3]
                    //     //           << " and " << face.vertices()[(i + 1) %
                    //     3]
                    //     //           << std::endl;
                    //     verts.push_back((verts[face.vertices()[i % 3]] +
                    //                      verts[face.vertices()[(i + 1) % 3]])
                    //                      /
                    //                     2);
                    // }

                    // std::cout << "face: " << face.vertices()[0] << ", "
                    //           << face.vertices()[1] << ", "
                    //           << face.vertices()[2] << std::endl;

                    a = middlepoint(face.vertices()[0], face.vertices()[1]);

                    b = middlepoint(face.vertices()[1], face.vertices()[2]);

                    c = middlepoint(face.vertices()[2], face.vertices()[0]);

                    new_fcs.push_back({{face.vertices()[0], a, c}});
                    new_fcs.push_back({{face.vertices()[1], b, a}});
                    new_fcs.push_back({{face.vertices()[2], c, b}});
                    new_fcs.push_back({{a, b, c}});

                    // for(flr::u64 i = 0; i < face.vertices().size(); i++) {
                    //     // std::cout << "pushing back " << i << " and "
                    //     //           << base_vertex + i + 1 << " and "
                    //     //           << base_vertex + ((i + 2) % 3) + 1 <<
                    //     //           std::endl;

                    //     new_fcs.push_back(
                    //         {{face.vertices()[i],
                    //           middlepoint(face.vertices()[i],
                    //                       face.vertices()[(i + 1) % 3]),
                    //           middlepoint(face.vertices()[(i + 2) % 3],
                    //                       face.vertices()[(i + 3) % 3])}});
                    // }

                    // new_fcs.push_back(
                    //     {{base_vertex + 1, base_vertex + 2, base_vertex +
                    //     3}});
                }

                fcs = std::vector<flr::Face>(new_fcs);
                new_fcs.clear();

                // for(auto & vert : verts) { vert /= vert.norm() / radius; }
            }
        }

        u64 middlepoint(u64 a, u64 b) {
            u64 smallerIndex = a < b ? a : b;
            u64 greaterIndex = a < b ? b : a;
            u64 key          = (smallerIndex << 32) + greaterIndex;
            // std::cout << "key for middle of " << smallerIndex << " and "
            //           << greaterIndex << " is " << key << std::endl;
            auto p = points.find(key);

            if(p != points.end()) {
                // std::cout << "key existed: " << p->second << std::endl;
                return p->second;
            }

            verts.push_back((verts[a] + verts[b]) / 2);

            points.insert(std::make_pair(key, verts.size() - 1));

            return verts.size() - 1;
        }

        std::vector<Edge> facesToEdges(std::vector<flr::Face> faces) {
            std::vector<Edge> edges;

            for(auto face : faces) {
                for(u64 i = 0; i < face.vertices().size(); i++) {
                    edges.push_back(
                        {face.vertices()[i],
                         face.vertices()[(i + 1) % face.vertices().size()]});
                }
            }

            std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
                if(a.x != b.x)
                    return a.x > b.x;
                else if(a.y != b.y)
                    return a.y > b.y;
                else
                    return true;
            });

            auto last = std::unique(edges.begin(), edges.end());
            edges.erase(last, edges.end());

            return edges;
        }

    private:
        std::unordered_map<u64, u64> points;
    };
}

#endif
