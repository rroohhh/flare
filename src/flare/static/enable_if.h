#ifndef _FLR_ENABLE_IF_H
#define _FLR_ENABLE_IF_H

namespace flr {
template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
    typedef T type;
};
}

#endif
