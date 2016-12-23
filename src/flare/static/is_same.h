#ifndef _FLR_IS_SAME_H
#define _FLR_IS_SAME_H

#include <algorithm>

namespace flr {
    template <class T, class U>
    struct is_same : std::false_type {};

    template <class T>
    struct is_same<T, T> : std::true_type {};
}

# endif
