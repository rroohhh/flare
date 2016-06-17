#ifndef _FLR_TYPE_NAME_H
#define _FLR_TYPE_NAME_H

#include "static_string.h"

namespace flr {
    template <typename T>
    constexpr flr::StaticString type_name() {
        flr::StaticString name = __PRETTY_FUNCTION__;
#ifdef __clang__
        return flr::StaticString(name.data() + 31, name.size() - 32);
#elif defined(__GNUC__)
#if __cplusplus < 201402
        return flr::StaticString(name.data() + 36, name.size() - 37);
#else
        return flr::StaticString(name.data() + 55, name.size() - 56);
#endif
#endif
    }
}

#endif
