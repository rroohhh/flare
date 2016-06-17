#include <iostream>

// #include "../flare/average.h"
#include "../flare/icosphere.h"
#include <iterator>
#include <list>
#include <vector>

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
    typedef T type;
};

template <class T, class U>
struct is_same : std::false_type {};

template <class T>
struct is_same<T, T> : std::true_type {};

template <typename... Ts>
struct make_void {
    typedef void type;
};

template <typename... Ts>
using void_t = typename make_void<Ts...>::type;

template <class, class = void_t<>>
struct hasBegin_ : std::false_type {};

template <class T>
struct hasBegin_<T, void_t<decltype(std::declval<T>().begin())>>
    : std::true_type {};

template <typename UnnamedType>
struct container {
private:
    template <typename... Params>
    constexpr auto test_validity(int /* unused */)
        -> decltype(std::declval<UnnamedType>()(std::declval<Params>()...),
                    std::true_type()) {
        return std::true_type();
    }

    template <typename... Params>
    constexpr std::false_type test_validity(...) {
        return std::false_type();
    }

public:
    template <typename... Params>
    constexpr auto operator()(Params &&...) {
        return test_validity<Params...>(int());
    }
};

template <typename UnnamedType>
constexpr auto is_valid_impl(UnnamedType && t) {
    return container<UnnamedType>();
}

#define __NARG__(...) __NARG_I_(, ##__VA_ARGS__, __RSEQ_N())
#define __NARG_I_(...) __ARG_N(__VA_ARGS__)
#define __ARG_N(_Z, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13,    \
                _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25,    \
                _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37,    \
                _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49,    \
                _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,    \
                _62, _63, N, ...)                                              \
    N

#define __RSEQ_N()                                                             \
    63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46,    \
        45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29,    \
        28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12,    \
        11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define _VFUNC_(name, n) name##n
#define _VFUNC(name, n) _VFUNC_(name, n)
#define VFUNC(func, ...) _VFUNC(func, __NARG__(__VA_ARGS__))(__VA_ARGS__)

#define EXPAND(X) X
#define FIRSTARG(X, ...) (X)
#define RESTARGS(X, ...) (__VA_ARGS__)

#define FOREACH(MACRO, LIST) FOREACH_(__NARG__ LIST, MACRO, LIST)

#define FOREACH_(N, M, LIST) FOREACH__(N, M, LIST)
#define FOREACH__(N, M, LIST) FOREACH_##N(M, LIST)
#define FOREACH_0(M, LIST)
#define FOREACH_1(M, LIST) M LIST
#define FOREACH_2(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_1(M, RESTARGS LIST)
#define FOREACH_3(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_2(M, RESTARGS LIST)
#define FOREACH_4(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_3(M, RESTARGS LIST)
#define FOREACH_5(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_4(M, RESTARGS LIST)
#define FOREACH_6(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_5(M, RESTARGS LIST)
#define FOREACH_7(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_6(M, RESTARGS LIST)
#define FOREACH_8(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_7(M, RESTARGS LIST)
#define FOREACH_9(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_8(M, RESTARGS LIST)
#define FOREACH_10(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_9(M, RESTARGS LIST)
#define FOREACH_11(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_10(M, RESTARGS LIST)
#define FOREACH_12(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_11(M, RESTARGS LIST)
#define FOREACH_13(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_12(M, RESTARGS LIST)
#define FOREACH_14(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_13(M, RESTARGS LIST)
#define FOREACH_15(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_14(M, RESTARGS LIST)
#define FOREACH_16(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_15(M, RESTARGS LIST)
#define FOREACH_17(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_16(M, RESTARGS LIST)
#define FOREACH_18(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_17(M, RESTARGS LIST)
#define FOREACH_19(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_18(M, RESTARGS LIST)
#define FOREACH_20(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_19(M, RESTARGS LIST)
#define FOREACH_21(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_20(M, RESTARGS LIST)
#define FOREACH_22(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_21(M, RESTARGS LIST)
#define FOREACH_23(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_22(M, RESTARGS LIST)
#define FOREACH_24(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_23(M, RESTARGS LIST)
#define FOREACH_25(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_24(M, RESTARGS LIST)
#define FOREACH_26(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_25(M, RESTARGS LIST)
#define FOREACH_27(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_26(M, RESTARGS LIST)
#define FOREACH_28(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_27(M, RESTARGS LIST)
#define FOREACH_29(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_28(M, RESTARGS LIST)
#define FOREACH_30(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_29(M, RESTARGS LIST)
#define FOREACH_31(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_30(M, RESTARGS LIST)
#define FOREACH_32(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_31(M, RESTARGS LIST)
#define FOREACH_33(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_32(M, RESTARGS LIST)
#define FOREACH_34(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_33(M, RESTARGS LIST)
#define FOREACH_35(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_34(M, RESTARGS LIST)
#define FOREACH_36(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_35(M, RESTARGS LIST)
#define FOREACH_37(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_36(M, RESTARGS LIST)
#define FOREACH_38(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_37(M, RESTARGS LIST)
#define FOREACH_39(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_38(M, RESTARGS LIST)
#define FOREACH_40(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_39(M, RESTARGS LIST)
#define FOREACH_41(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_40(M, RESTARGS LIST)
#define FOREACH_42(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_41(M, RESTARGS LIST)
#define FOREACH_43(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_42(M, RESTARGS LIST)
#define FOREACH_44(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_43(M, RESTARGS LIST)
#define FOREACH_45(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_44(M, RESTARGS LIST)
#define FOREACH_46(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_45(M, RESTARGS LIST)
#define FOREACH_47(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_46(M, RESTARGS LIST)
#define FOREACH_48(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_47(M, RESTARGS LIST)
#define FOREACH_49(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_48(M, RESTARGS LIST)
#define FOREACH_50(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_49(M, RESTARGS LIST)
#define FOREACH_51(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_50(M, RESTARGS LIST)
#define FOREACH_52(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_51(M, RESTARGS LIST)
#define FOREACH_53(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_52(M, RESTARGS LIST)
#define FOREACH_54(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_53(M, RESTARGS LIST)
#define FOREACH_55(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_54(M, RESTARGS LIST)
#define FOREACH_56(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_55(M, RESTARGS LIST)
#define FOREACH_57(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_56(M, RESTARGS LIST)
#define FOREACH_58(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_57(M, RESTARGS LIST)
#define FOREACH_59(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_58(M, RESTARGS LIST)
#define FOREACH_60(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_59(M, RESTARGS LIST)
#define FOREACH_61(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_60(M, RESTARGS LIST)
#define FOREACH_62(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_61(M, RESTARGS LIST)
#define FOREACH_63(M, LIST) EXPAND(M FIRSTARG LIST) FOREACH_62(M, RESTARGS LIST)

#define FOREACH_BUT_FIRST(M1, M2, FIRST, ...)                                  \
    M1(FIRST) FOREACH(M2, (__VA_ARGS__))

#define TO_ARG(X) , TO_FIRST_ARG(X)
#define TO_FIRST_ARG(X) auto && X

#define SINGLE_ARG(...) __VA_ARGS__
#define EXPRESSIONS(...) SINGLE_ARG(__VA_ARGS__)

#define is_valid(expr, ...)                                                    \
    is_valid_impl([](FOREACH_BUT_FIRST(TO_FIRST_ARG, TO_ARG,                   \
                                       __VA_ARGS__)) -> decltype(expr) {})
#define valid(CHECKER) decltype(CHECKER)::value

auto hasBegin     = is_valid(t.begin(), t);
auto hasEnd       = is_valid(t.end(), t);
auto hasIncrement = is_valid(++t, t);
auto hasDeref     = is_valid(*t, t);
auto canRangeBasedFor =
    is_valid(EXPRESSIONS(hasBegin(t), hasEnd(t), hasIncrement(t.begin()),
                         hasDeref(t.begin())),
             t);

template <typename T>
auto average(T t) -> typename enable_if<valid(canRangeBasedFor(t)),
                                        decltype(*(t.begin()))>::type {
    std::cout << "can do stuff ";
    return *t.begin();
}

template <typename T>
auto average(T t) -> typename enable_if<!valid(canRangeBasedFor(t))>::type {
    static_assert(is_same<T, T *>(),
                  "average has to be used with a type "
                  "having begin(), end(), operator *begin() and ++begin()");
}

#define RETURN(X) X
#define where(expr, return_type) typename enable_if<(expr), return_type>::type

template <int i>
where(i > 5, RETURN(char)) variant() {
    return 'y';
}

template <int i>
where(!(i > 5), RETURN(char)) variant() {
    return 'n';
}

struct test {
    void begin();
    void end();
};

int main() {
    std::vector<flr::Face> fcs = {
        {{0, 1, 2}}, {{0, 1, 3}}, {{0, 2, 3}}, {{1, 2, 4}}};

    std::vector<flr::v3> verts = {
        {-1, -1, -1}, {1, 1, -1}, {1, -1, 1}, {-1, 1, 1}};

    flr::IcoSphere s(flr::Mesh(verts, fcs), 1, 9);
	s.printCSV();
}
