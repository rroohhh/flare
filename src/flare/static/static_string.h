#ifndef _FLR_STATIC_STRING_H
#define _FLR_STATIC_STRING_H

#include "../type/types.h"
#include <cstddef>
#include <cstring>
#include <ostream>
#include <stdexcept>

namespace flr {
    class StaticString {
    private:
        const char * const d;
        const flr::u64     s;

    public:
        typedef const char * const_iterator;

        template <flr::u64 n>
        constexpr StaticString(const char (&string)[n]) noexcept
            : d(string), s(n - 1) {}

        constexpr StaticString(const char * string, flr::u64 n) noexcept
            : d(string), s(n) {}

        constexpr const char * data() const noexcept { return d; }
        constexpr flr::u64     size() const noexcept { return s; }

        constexpr const_iterator begin() const noexcept { return d; }
        constexpr const_iterator end() const noexcept { return d + s; }

        constexpr char operator[](flr::u64 n) const {
            return n < s ? d[n] : throw std::out_of_range("static_string");
        }

		std::string toStdString() {
			return std::string(d, s);
		}
    };

    inline std::ostream & operator<<(std::ostream &       os,
                                     StaticString const & s) {
        return os.write(s.data(), s.size());
    }
}
#endif
