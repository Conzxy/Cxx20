#include <memory>

// constinit = constexpr - const
// 尽管这很反直觉
constinit int a = 1;
const constinit int b = 2;

// constinit auto c = a; // error: a is not constant even though it is evaluated in compile time
constinit auto d = b;
constinit std::unique_ptr<int> up; // The constructor of class must be declared to constexpr

class Test {
    static constinit int a;// = 2; // error: a is not a inline variable
    static constexpr int b = 3; // constexpr implicit inline
};

constinit int Test::a = 2;

extern constinit int x;

constinit int x = 42;

auto main() -> int {
    a = 2;
    // b = 1;
}