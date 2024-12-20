#include <thread>
#include <ranges>
#include <string>
#include <vector>

#include "util/fmt.h"

using namespace std::ranges;
using namespace std;

// 给定一个string[], key, 找到key在string中的索引, 没有, 返回-1
// @see Tour of C++(3rd) 18.5.4 Stopping a thread

// std::ranges::iterator_t is a decltype and declval wrapper of std::ranges::begin()
template <range R>
void parallel_find(std::stop_token tok, std::ranges::iterator_t<R> base, R&& range, const std::string& target, std::atomic<int>& result)
{
    for (auto p = std::ranges::begin(range); p != std::ranges::end(range) && !tok.stop_requested(); ++p) {
        if (*p == target) {
            result = std::ranges::distance(base, p);
            return;
        }
    }
}

auto main() -> int {
    std::atomic<int> result = -1;

    std::vector<std::string> text {
        "a", "b", "c", "d", "e", "f"
    };

    std::string key = "f";
    stop_source ss1{};
    stop_source ss2{};

    const int mid = text.size() / 2;

    const auto slice1 = std::span{text.begin(), text.begin() + mid};
    const auto slice2 = std::span{text.begin() + mid, text.end()};
    parallel_find(ss1.get_token(), slice1.begin(), slice1, key, result);
    parallel_find(ss2.get_token(), slice1.begin(), slice2, key, result);

    while (result == -1) {
        std::this_thread::sleep_for(10ms);
    }

    ss1.request_stop();
    ss2.request_stop();

    fmt::println("result = {}", result.load());
}