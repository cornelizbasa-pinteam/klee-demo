#include <assert.h>
#ifdef KLEE
#include <klee/klee.h>
#endif

constexpr auto N { 4 };

int main(int argc, char* argv[])
{
    unsigned char a[N];
#ifdef KLEE
    klee_make_symbolic(&a[0], N * (sizeof a[0]), "a");
#endif
    auto sum { 0 };
    auto prod { 1 };
    for (auto i = 0; i < N; ++i) {
        sum += a[i];
        prod *= a[i];
    }
    assert(!(a[0] != 0 && sum == prod));
    return 0;
}
