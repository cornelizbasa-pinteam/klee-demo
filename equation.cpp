#ifdef KLEE
#include <klee/klee.h>
#endif
#include <cassert>

int f(int x)
{
    return x * x - 2 * x + 1;
}

int main(int argc, char* argv[])
{
    int x;
#ifdef KLEE
    klee_make_symbolic(&x, sizeof x, "x");
#endif
    auto y = f(x);
#ifdef KLEE
    assert(y != 0);
#endif
    return y;
}
