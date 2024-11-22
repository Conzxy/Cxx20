#include "util/fmt.h"

#include <numbers>

int main()
{
    fmt::println("int: {}, float: {}, bool: {}, str: {}", 1, 2., true, "xx");
    // The : prefix must be set, and you can select a char to fill,
    // if no char selected, will fill by spaces
    // No prefix will trigger abort.

    // > indicates char wll be placed location, the remaining will be filled
    fmt::println("left: {:,>4}, mid: {:.^4}, right: {:<4}", 32, 32, 32);

    // NOTE: decimal including number and fractional part
    fmt::println("pi with 5 decimal precision: {:.5}", std::numbers::pi);

    fmt::println("pi with 5 fractional part precision and align: {:.<35.5f}", std::numbers::pi);
    return 0;
}
