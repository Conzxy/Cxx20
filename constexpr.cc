#include <memory>
#include <vector>
#include "util/fmt.h"

// 以下展示constexpr的一个坑

consteval auto f() {
    auto p = new std::vector{ 1, 2, 3 };
#if 1
    auto ret = p->at(0);
    delete p;
    return ret;
#else
    return p;
#endif
}

__declspec(allocator) constexpr void *my_alloc(std::size_t size) { return ::operator new(size); }
constexpr void my_free(void *p, std::size_t size) { ::operator delete(p, size); }

consteval auto g() {
    // return p;
    std::allocator<char> a;
    auto p = my_alloc(10);
    my_free(p, 10);
}

auto main() -> int {
    // constexpr auto p = f();
    g();
}