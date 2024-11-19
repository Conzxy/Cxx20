// Test copy elision(or RVO)
// The copy elision is enabled even in C++98
// don't test some complex cases.

// Please compile this program in gcc:
// g++ -o demo copy_elision.cc -std=c++98
#include <stdio.h>
#include <type_traits>

struct A {
  A() = default;

  A(A const &) {
    printf("Copy from A\n");
  }

  A &operator=(A const &)
  {
    printf("Copy operator\n");
    return *this;
  }

#if __cplusplus > 201103L
  A &operator=(A &&)
  {
    printf("Move operator\n");
    return *this;
  }
#endif

  friend A operator+(A const &a, A const &b)
  {
    return A();
  }
};

int main() {
  A a, b, c;
  A d = a + b + c;
}
