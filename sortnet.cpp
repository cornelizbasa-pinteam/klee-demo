// See: https://en.wikipedia.org/wiki/Sorting_network

#ifdef KLEE
#include <klee/klee.h>
#include <assert.h>
#else
#include <stdio.h>
#endif // KLEE

#include <cstdint>
#include <cstddef>

#define N (3)
#define NET_N (3)

using element_t = uint8_t;

struct cmp {
    uint8_t x;
    uint8_t y;
};

using net_t = cmp[NET_N];

void sortnet(element_t a[N], net_t net)
{
    for (size_t i = 0; i < NET_N; ++i) {
        if (a[net[i].x] > a[net[i].y]) {
            auto aux = a[net[i].x];
            a[net[i].x] = a[net[i].y];
            a[net[i].y] = aux;
        }   
    }
}

bool sorted(element_t a[N]) {
    for (size_t i = 0; i < N - 1; ++i) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
	element_t a[N];
    net_t net;
#ifdef KLEE
    klee_make_symbolic(&net, sizeof(net[0]) * NET_N, "net");
    // Accept only valid comparison networks with standard representation (x < y).
    for (size_t i = 0; i < NET_N; ++i) {
        if (net[i].x >= N) {
            return 1;
        }
        if (net[i].y >= N) {
            return 1;
        }
        if (net[i].x >= net[i].y) {
            return 1;
        }
    }
    // Constrain the result to networks that sort all relevant 3-element arrays.
    for (uint8_t i = 0; i < N; ++i) {
        for (uint8_t j = 0; j < N; ++j) {
            for (uint8_t k = 0; k < N; ++k) {
                a[0] = i;
                a[1] = j;
                a[2] = k;
                sortnet(a, net);
                if (!sorted(a)) {
                    return 1;
                }
            }
        }
    }
    klee_assert(false);
#endif
    return 0;
}