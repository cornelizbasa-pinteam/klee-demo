#include <assert.h>
#ifdef KLEE
#include <klee/klee.h>
#endif

int main(int argc, char* argv[])
{
    unsigned int n { 133127 };
    unsigned int div;
#ifdef KLEE
    klee_make_symbolic(&div, sizeof div, "div");
#endif
    assert(!(div > 1 && div != n && n % div == 0));
    return 0;
}
