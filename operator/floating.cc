#include <compare>
#include <cmath>
#include <limits>
#include <cassert>

#include "util/fmt.h"

// @see https://realtimecollisiondetection.net/blog/?p=89

template <std::floating_point T>
[[nodiscard]] bool fuzzy_compare_absolute(T a, T b) noexcept {
    fmt::println("{} {} {}", a, b, std::fabs(a - b));
    return std::fabs(a - b) < std::numeric_limits<T>::epsilon();
}

template <std::floating_point T>
[[nodiscard]] bool fuzzy_compare_relative(T a, T b) noexcept {
    return std::fabs(a - b) < std::numeric_limits<T>::epsilon() * std::max(std::fabs(a), std::fabs(b));
}

template <std::floating_point T>
[[nodiscard]] bool fuzzy_compare_tradeoff(T a, T b) noexcept {
    return std::fabs(a - b) < std::numeric_limits<T>::epsilon() * std::max(static_cast<T>(1), std::max(std::fabs(a), std::fabs(b)));
}

auto main() -> int {
    constexpr double a = .1 + .2;
    constexpr double b = .3;

    static_assert(a != b);
    assert(fuzzy_compare_relative(a, b));
    assert(!fuzzy_compare_relative(1e-6f, 1e-6f+1e-7f)); // relative fuzzy compare will fail when given value is small
    assert(!fuzzy_compare_absolute(1e6f, 1e6f+.01f)); // absolute fuzzy compare will fail when given value is large
    assert(fuzzy_compare_tradeoff(1e6f, 1e6f+.001f));
    assert(fuzzy_compare_tradeoff(1e-6f, 1e-6f+1e-7f));
}