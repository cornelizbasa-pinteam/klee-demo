// See: https://en.wikipedia.org/wiki/Taxicab_number

#include <assert.h>
#ifdef KLEE
#include <klee/klee.h>
#endif

constexpr auto N = 17;

#define SYM(x)                                                                 \
    {                                                                          \
        klee_make_symbolic(&x, sizeof x, #x);                                  \
    }

int main()
{
    unsigned int a, b, c, d;

#ifdef KLEE
    SYM(a);
    SYM(b);
    SYM(c);
    SYM(d);
    if (a < N && b < N && c < N && d < N && a != c && a != d) {
        klee_assert(a * a * a + b * b * b != c * c * c + d * d * d);
    }
#endif

    return 0;
}
