#include <cstdio>
#include <type_traits>
#include <vector>

consteval int sqr(int n)
{
    return n*n;
}
constexpr int r = sqr(100); // OK

int x = 100;
// int r2 = sqr(x);            // Error: Call does not produce a constant

consteval int sqrsqr(int n)
{
    // static_assert(std::is_constant_evaluated()); // true forever
    return sqr(sqr(n));     // Not a constant expression at this point, but OK
}

constexpr int sqrsqr2(int n) {
    // The static_assert must be evaluated in compile time
    // static_assert(std::is_constant_evaluated());
    // To `constexpr if`, same as above
    // Must use if here.
    if (std::is_constant_evaluated()) {
        return 3;
    }
    return n * n;
}

// consteval is ok, the n is forced be compile-time constant
#if 0
constexpr int dblsqr(int n)
{
    return 2 * sqr(n);      // Error: Enclosing function is not consteval
                            // and sqr(n) is not a constant
}
#endif

constexpr std::vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
auto main() -> int {
    [[maybe_unused]]
    auto a = sqrsqr(100);
    [[maybe_unused]]
#if 0
    auto b = sqrsqr2(2); // runtime context
    // sqrsqr2()并未用于给编译时常量求值，在编译器看来，b是一个运行时值，
    // 这并不是constant expression

    // print 4
#else
    constexpr auto b = sqrsqr2(2); // compile context
    // print 3
#endif
    printf("%d\n", b);
}