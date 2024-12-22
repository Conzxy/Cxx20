#include <ranges>
#include <iostream>

auto main() -> int {
    auto v1 = std::ranges::empty_view<int>{}; // 用于返回空view?
    auto v2 = std::ranges::single_view{1};

    auto v3 = std::ranges::iota_view{0};
    auto v4 = std::ranges::iota_view{0, 10};

    auto v5 = std::ranges::istream_view<int>(std::cin);
}