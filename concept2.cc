#include <type_traits>
#include <numeric>
#include <memory>

#include "util/fmt.h"

#if 1
template <typename T>
struct IsUniquePtr : std::false_type {};

template <typename U, typename D>
struct IsUniquePtr<std::unique_ptr<U, D>> : std::true_type {};

template <typename T>
struct IsSharedPtr : std::false_type {};

template <typename T>
struct IsSharedPtr<std::shared_ptr<T>> : std::true_type {};
#else
// tricky but buggy
// These predicates requires the T has element_type or deleter_type
template <typename T>
constexpr bool IsUniquePtr_v = std::is_same_v<std::decay_t<T>, std::unique_ptr<typename T::element_type, typename T::deleter_type>>;

template <typename T>
constexpr bool IsSharedPtr_v = std::is_same_v<std::decay_t<T>, std::shared_ptr<typename T::element_type>>;

template <typename T>
struct IsUniquePtr : std::bool_constant<IsUniquePtr_v<T>> {};

template <typename T>
struct IsSharedPtr : std::bool_constant<IsSharedPtr_v<T>> {};
#endif

// WANING: The IsSharedPtr<T> must be in the left of the IsUniquePtr.
template <typename T>
concept IsPointer = std::disjunction_v<std::is_pointer<T>, IsSharedPtr<T>, IsUniquePtr<T>>;

template <typename T>
requires (!IsPointer<T>)
constexpr T GoodMax(T const &x, T const &y) noexcept(noexcept(std::max(x, y)))
{
    return std::max(x, y);
}

template <IsPointer T>
constexpr auto GoodMax(T const &x, T const &y) noexcept(noexcept(std::max(*x, *y)))
{
    return std::max(*x, *y);
}

auto main() -> int {
    static constexpr int x = 1;
    static constexpr int y = 2;

    static_assert(2 == GoodMax(&x, &y));

    fmt::println("{}", GoodMax(std::make_unique<int>(1), std::make_unique<int>(2)));

    fmt::println("{}", GoodMax(std::make_shared<int>(3), std::make_shared<int>(4)));

    GoodMax(1, 2);
}

