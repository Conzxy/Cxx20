#include <vector>
#include <algorithm>

#include "util/fmt.h"

// Usage:
// 1. 可以在函数内定义泛型lambda（局部）
// 2. 传递predicate不需要指定模板实参，通配functor
auto printElem = [](const auto& cont) {
    for (const auto& e : cont) {
        fmt::println("{}", e);
    }
};

// template <typename T>
// void printElemF(const T& cont);

void printElemF(const auto& cont);

// auto可以视作T的语法糖
void printElemF(const auto& cont) {
    for (const auto& e : cont) {
        fmt::println("{}", e);
    }
}

// Also, you can use std::same_as concept to replace
template <typename T>
concept IsVector = std::is_same_v<T, std::decay_t<std::vector<typename T::value_type>>>;

auto printElemV = [](const IsVector auto& vec) {
    for (const auto& e : vec) {
        fmt::println("{}", e);
    }
};

#if 0
// 将编译时Int塞入参数列表是无法实现正常的Iterator的
template <int Idx, typename ...Args>
struct TupleIter {
 public:
    const std::tuple<Args...>& tuple_;

    constexpr TupleIter(const std::tuple<Args...>& rhs)
        : tuple_{ rhs }
    {}

    TupleIter<Idx+1, Args...> operator++() noexcept
    {
        return { tuple_ };
    }

    TupleIter<Idx-1, Args...> operator--() noexcept
    {
        return { tuple_ };
    }

    auto operator*() noexcept -> decltype(std::get<Idx>(tuple_)) {
        return std::get<Idx>(tuple_);
    }

    auto operator*() const noexcept {
        return std::get<Idx>(tuple_);
    }

    template <int Idx2>
    bool operator==(const TupleIter<Idx2, Args...>& rhs) const noexcept {
        return Idx2 == Idx && &rhs.tuple_ == &tuple_;
    }
};

template <typename ...Args>
constexpr auto begin(const std::tuple<Args...>& tpl) {
    return TupleIter<0, Args...>{ tpl };
}

template <typename ...Args>
constexpr auto end(const std::tuple<Args...>& tpl) {
    return TupleIter<sizeof...(Args)-1, Args...>{ tpl };
}

template <typename ...Args>
struct TupleIter {
 public:
    const std::tuple<Args...>& tuple_;
    int idx_;

    constexpr TupleIter(int idx, const std::tuple<Args...>& rhs)
        : tuple_{ rhs }
        , idx_{ idx }
    {}

    constexpr TupleIter<Args...> &operator++() noexcept
    {
        ++idx_;
        return *this;
    }

    constexpr TupleIter<Args...> operator--() noexcept
    {
        --idx_;
        return *this;
    }

    constexpr auto operator*() noexcept -> decltype(std::get<idx_>(tuple_)) {
        return std::get<idx_>(tuple_);
    }

    constexpr auto operator*() const noexcept {
        return std::get<idx_>(tuple_);
    }

    constexpr bool operator==(const TupleIter<Args...>& rhs) const noexcept {
        return rhs.idx_ == idx_ && &rhs.tuple_ == &tuple_;
    }
};

template <typename ...Args>
constexpr auto begin(const std::tuple<Args...>& tpl) {
    return TupleIter<Args...>{ 0, tpl };
}

template <typename ...Args>
constexpr auto end(const std::tuple<Args...>& tpl) {
    return TupleIter<Args...>{ sizeof...(Args)-1, tpl };
}
#endif


auto main() -> int {
    printElem(std::vector{ 1, 2, 3 });
    printElemF(std::vector{ 1, 2, 3 });
    printElemV(std::vector{ 1, 2, 3 });
    // printElemV(std::initializer_list{1, 2, 3}); // Error!

    // Note: constexpr可以不加，似乎默认constexpr
    constexpr auto LessBySize = [](const auto& lhs, const auto& rhs) {
        return lhs.size() < rhs.size();
    };

    std::vector<std::string> strs{ "12", "1", "1234", "123" };
    std::sort(std::ranges::begin(strs), std::ranges::end(strs), LessBySize);
    printElemV(strs);

    // 指定泛型lambda的模板实参
    static_assert(LessBySize.operator()<std::string, std::string>("xx", "sasdf"));

}