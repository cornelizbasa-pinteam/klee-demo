#ifdef KLEE
#include <klee/klee.h>
#endif
#include <cstdlib>
#include <assert.h>

int f(int x)
{
    // if (x > 2) {
    //     return x - 2;
    // }
    return x * x - 2 * x + 1;
}

int main(int argc, char* argv[])
{
    int x = atoi(argv[1]);
    auto y = f(x);
#ifdef KLEE
    assert(y != 0);
#endif
    return y;
}
