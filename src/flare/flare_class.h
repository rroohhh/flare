#ifndef _FLR_FLARECLASS_H
#define _FLR_FLARECLASS_H

#include "tracker.h"

#define FLARE_CLASS(name) class name : private flr::internal::FlareClass<name>
#define FLARE_UNION(name) union name : private flr::internal::FlareClass<name>
#define FLARE_STRUCT(name) struct name : private flr::internal::FlareClass<name>

namespace flr {
    namespace internal {
        template <typename T>
        class FlareClass : private flr::internal::Tracker<T> {};
    }
}

#endif
