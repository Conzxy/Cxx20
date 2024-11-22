#include <vector>
#include <ranges>
#include <numeric>
#include <type_traits>

#include "util/fmt.h"

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

template <Numeric T>
void print_number(T x) {
    fmt::println("number: {}", x);
}

template <typename T>
requires std::is_integral_v<typename T::value_type>
constexpr double avg(T const &arr) {
    return std::reduce(std::ranges::begin(arr), std::ranges::end(arr)) / std::ranges::size(arr);
}

struct VectorWrapper {
    std::vector<int> arr_ = { 1, 2, 3 };

    using value_type = decltype(arr_)::value_type;
};

auto begin(VectorWrapper const &vw) noexcept -> decltype(vw.arr_.begin()) {
    return vw.arr_.begin();
}

auto end(VectorWrapper const &vw) noexcept -> decltype(vw.arr_.end()){
    return vw.arr_.end();
}

auto size(VectorWrapper const &vw) noexcept -> decltype(vw.arr_.size()) {
    return vw.arr_.size();
}

int main() {
    print_number(1.32);
    print_number(20);
    // print_number((void*)1);

    // Because the vector must be constructed in runtime, the constexpr optimization does not work.
    print_number(avg(std::vector{1, 2, 3}));

    // Test ADL overload branch
    // Also, the optimization does not work
    print_number(avg(VectorWrapper{}));

}
