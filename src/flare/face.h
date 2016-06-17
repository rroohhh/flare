#ifndef _FLR_FACE_H
#define _FLR_FACE_H

#include "flare_class.h"
#include <vector>

namespace flr {
    FLARE_CLASS(Face) {
    public:
        Face(std::vector<u64> vertices) : vertices_(vertices) {}

		auto vertices() {
			return vertices_;
		}
    private:
        std::vector<u64> vertices_;
    };
}

#endif
