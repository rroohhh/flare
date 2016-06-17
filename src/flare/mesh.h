#ifndef _FLR_MESH_H
#define _FLR_MESH_H

#include "face.h"
#include "flare_class.h"
#include "types.h"
#include "vector.h"
#include <vector>
#include <stdio.h>

namespace flr {
    FLARE_CLASS(Mesh) {
        using v3 = flr::v3;

    public:
		Mesh() {}
        Mesh(std::vector<v3> & verts, std::vector<flr::Face> & faces)
            : verts(verts), fcs(faces) {}

        auto & points() { return verts; }
        auto & faces() { return fcs; }

        void printCSV() {
			for(auto vert : verts) {
				printf("%lf, %lf, %lf\n", vert.x, vert.y, vert.z);
			}
		}
    protected:
        std::vector<v3>        verts;
        std::vector<flr::Face> fcs;
    };
}

#endif
