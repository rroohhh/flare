#ifndef _FLR_ICOSPHERE_H
#define _FLR_ICOSPHERE_H

#include "flare_class.h"
#include "mesh.h"
#include "types.h"
#include "vector.h"
#include <algorithm>

namespace flr {
    FLARE_CLASS(IcoSphere), public Mesh {
        using v3 = flr::v3;

    public:
        IcoSphere(flr::Mesh base, flr::f64 radius, flr::u64 subdiv) {
            v3       center = {0, 0, 0};
            flr::u64 this_vertex;

            for(auto vert : base.points()) { center += vert; }

            center /= base.points().size();

            // center = flr::average(base.points());

            for(auto vert : base.points()) { verts.push_back(vert - center); }

            std::vector<flr::Face> new_fcs;
            fcs = std::vector<flr::Face>(base.faces());
            std::vector<std::pair<flr::u64, flr::f64>> angles;

            flr::u64 this_index;
            flr::u64 next_index;
            flr::u64 new_index;

            for(u64 i = 0; i < subdiv; i++) {
                new_fcs.clear();

                for(auto face : fcs) {
                    center = {0, 0, 0};

                    for(auto vertex : face.vertices()) {
                        center += verts[vertex];
                    }

                    verts.push_back(center / face.vertices().size());
                    new_index = verts.size() - 1;

                    angles.clear();
                    angles.push_back(std::make_pair(face.vertices()[0], 0));

                    for(u64 i = 1; i < face.vertices().size(); i++) {
                        this_vertex = face.vertices()[i];

                        angles.push_back(std::make_pair(
                            this_vertex, verts[this_vertex].angleBetween(
                                             verts[face.vertices()[0]])));
                    }

                    std::sort(angles.begin(), angles.end(), [](auto a, auto b) {
                        return a.second < b.second;
                    });

                    angles.push_back(std::make_pair(face.vertices()[0], 0));

                    for(flr::u64 i = 0; i < angles.size() - 1; i++) {
                        this_index = angles[i].first;
                        next_index = angles[i + 1].first;
                        new_fcs.push_back(std::vector<u64>(
                            {new_index, this_index, next_index}));
                    }
                }

                fcs = std::vector<flr::Face>(new_fcs);

                for(auto & vert : verts) { vert /= vert.norm(); }
            }
        }
    };
}

#endif
