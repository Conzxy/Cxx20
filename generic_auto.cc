#include <vector>
#include <ranges>

#include "util/fmt.h"

auto printElem = [](const auto& cont) {
    for (const auto& e : cont) {
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
}
