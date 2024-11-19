#include <iostream>
#include <format>

int main()
{
    std::cout << std::format("{} {} {}", 1, "xx", 1.) << std::endl;
    return 0;
}
