consteval int sqr(int n)
{
    return n*n;
}
constexpr int r = sqr(100); // OK

int x = 100;
// int r2 = sqr(x);            // Error: Call does not produce a constant

consteval int sqrsqr(int n)
{
    return sqr(sqr(n));     // Not a constant expression at this point, but OK
}

// consteval is ok, the n is forced be compile-time constant
constexpr int dblsqr(int n)
{
    return 2 * sqr(n);      // Error: Enclosing function is not consteval
                       // and sqr(n) is not a constant
}

auto main() -> int {

}