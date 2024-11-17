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

  friend A operator+(A const &a, A const &b)
  {
    return A();
  }
};

int main() {
  A a, b, c;
  A d = a + b + c;

  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (auto i : arr)
  {
    printf("%d\n", i);
  }
  // static_assert(0);
}
