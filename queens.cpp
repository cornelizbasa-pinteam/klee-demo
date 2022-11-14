#include <assert.h>
#include <cstdlib>

#ifdef KLEE
#include <klee/klee.h>
#endif

constexpr auto N = 8;

unsigned char queens[N];

bool attack()
{
    for (auto i = 0; i < N; i++) {
        for (auto j = i + 1; j < N; j++) {
            if ((queens[i] == queens[j]) || (abs(queens[i] - queens[j]) == j - i)) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
#ifdef KLEE
    klee_make_symbolic(&queens[0], N * (sizeof queens[0]), "queens");

    for (auto& q : queens) {
        klee_assume(q < N);
    }

    klee_assert(attack());
#endif

    return 0;
}
