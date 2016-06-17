#ifndef _FLR_AVERAGE_H
#define _FLR_AVERAGE_H

#include "types.h"
#include <iterator>

namespace flr {
	template<typename T>
	constexpr auto average(T data) {
		typename std::iterator_traits<T>::value_type tmp;
		u64 count = 0;
		for(auto elem : data) {
			tmp += elem;
			count++;
		}

		tmp /= count;

		return tmp;
	}
}

#endif
