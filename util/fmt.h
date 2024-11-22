#ifndef _CXX20_FMT_H__
#define _CXX20_FMT_H__

#include <format>
#include <string>
#include <string_view>

namespace fmt {

// The args is read-only, no need to use perfect forward(ie. Args&&)
template <typename... Args>
void print(std::string_view fmt, Args const&... args) noexcept
{
    fputs(std::vformat(fmt, std::make_format_args(args...)).c_str(), stdout);
}

template <typename... Args>
void println(std::string_view fmt, Args const&... args) noexcept
{
    puts(std::vformat(fmt, std::make_format_args(args...)).c_str());
}

} // namespace fmt

#endif