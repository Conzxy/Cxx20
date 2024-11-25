#include <array>
#include <numeric>
#include <ranges>

consteval auto process() {
    std::array a { 1, 2, 3 };
    return std::reduce(std::ranges::begin(a), std::ranges::end(a));
}

auto main() -> int {
    auto n = process();
    // static_assert(n == 6);
}