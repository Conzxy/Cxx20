#include <utility>
#include <vector>
#include <string>
#include <iostream>

// 结合这个blog看:
// https://quuxplusone.github.io/blog/2023/09/08/constexpr-string-firewall/

// Use the default deleter: delete operator
// The std::unique_ptr<T> use constexpr in C++23.
// In C++20, it just a inline function(see _CONSTEXPR23),
// so we should implement a simple unique_ptr to replace it.
template <typename T>
class UniquePtr {
 public:
    constexpr UniquePtr(): ptr_{ nullptr } {}
    constexpr explicit UniquePtr(std::nullptr_t): ptr_{ nullptr } {}
    constexpr explicit UniquePtr(T *ptr): ptr_{ ptr }
    {}

    constexpr ~UniquePtr() noexcept { delete ptr_; }

    UniquePtr(UniquePtr const &) = delete;
    UniquePtr &operator=(UniquePtr const &) = delete;

    constexpr UniquePtr(UniquePtr &&o) noexcept
        : ptr_{ o.ptr_ }
    {
        o.ptr_ = nullptr;
    }

    constexpr UniquePtr &operator=(UniquePtr &&o) noexcept
    {
        std::swap(ptr_, o.ptr_);
    }

    constexpr T *get() noexcept { return ptr_; }
    constexpr T const *get() const noexcept { return ptr_; }

    constexpr T &operator*() noexcept { return *ptr_; }
    constexpr T const &operator*() const noexcept { return *ptr_; }

    constexpr T *operator->() noexcept { return ptr_; }
    constexpr T const *operator->() const noexcept { return ptr_; }

    template <typename U>
    constexpr bool operator==(UniquePtr<U> const &rhs) const noexcept { return ptr_ == rhs.ptr_; }

    template <typename U>
    constexpr bool operator!=(UniquePtr<U> const &rhs) const noexcept { return ptr_ != rhs.ptr_; }

    template <typename U>
    constexpr bool operator==(U *ptr) const noexcept { return ptr_ == ptr; }

    template <typename U>
    constexpr bool operator!=(U *ptr) const noexcept { return ptr_ != ptr; }

    constexpr bool operator==(std::nullptr_t ) const noexcept { return ptr_; }
    constexpr bool operator!=(std::nullptr_t) const noexcept { return !ptr_; }
 private:
    T *ptr_;
};

template <typename T, typename... Args>
constexpr auto MakeUnique(Args &&...args) -> UniquePtr<T>
{
    return UniquePtr(new T{ std::forward<Args>(args)... }) ;
}

constexpr auto g()
{ return MakeUnique<int>(42); }

static_assert(*g() == 42);
[[maybe_unused]] constexpr int i = *g(); // OK
[[maybe_unused]] constexpr bool gt = (g() != nullptr); // OK
// constexpr auto p = g(); // Error! The fake address is assigned to a runtime variable even though the value is computed at compile time

#if 0
// The fake allocation memory doesn't freed
constexpr auto f()
{ return new int{ 42 }; }

static_assert(*f() == 42);
#endif

auto main() -> int {
    // The vector pointer to a fake-heap address which is allocated at compile time
    // constexpr std::vector v { 1, 2, 3 }; // Error!

    // This is OK, because the v is an empty vector, don't allocated any memory at compile time or runtime
    constexpr std::vector<int> v{};

    // constexpr std::string str2{ "1121132q213423q523453" }; // Error!

    // You can think string memory layout as following:
    // libstdc++:
    // struct string {
    //     char data_* = &sso_buffer_;
    //     union {
    //         char sso_buffer_[16];
    //         struct {
    //            size_t size_;
    //            size_t capacity_;
    //         };
    //     };
    // };
    // After C++11, the string use SSO optimization to implement.

    constexpr std::string str{ "11" };  // Error!(To Gcc)
    // The data will pointer to a fake stack when SSO is enabeld.
}