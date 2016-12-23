#ifndef _FLR_NULL_TYPE_H
#define _FLR_NULL_TYPE_H

// ToDo(robin): Is this everything needed?

namespace flr {
	class NullType {
    public:
        NullType() = delete;

        NullType(NullType & other) = delete;

        ~NullType() = delete;
    };
}

#endif
