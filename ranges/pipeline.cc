#include <ranges>
#include <vector>

auto get_even_view(std::ranges::forward_range auto&& nums)
{
    return nums |
        std::views::filter([](const auto x) { return x % 2 == 0; }) |
        std::views::take_while([](const auto x) { return x < 6; });
}

auto main() -> int {
    std::vector nums { 1, 2, 3, 4, 5, 6 };

    for (const auto even : get_even_view(nums))
    {
        printf("%d\n", even);
    }
}