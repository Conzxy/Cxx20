#include <ranges>
#include <algorithm>
#include <vector>
#include <list>

#include "util/fmt.h"

namespace rg = std::ranges;
namespace vw = rg::views;

auto main() -> int {
    std::vector vec{ 1, 2, 3, 4, 5 };
    rg::sort(vec, std::greater<int>());

    fmt::print_elements(vec);

    // fmt::print_elements(rg::sort(std::vector{1, 2, 3, 4 })); // Error! dangling view
    // rg::sort(std::list{ 1, 2, 3 }); // Error!

}