#include <assert.h>
#ifdef KLEE
#include <klee/klee.h>
#endif

#include <cstring>
#include <iostream>

constexpr int N = 5;

void login(const char* user)
{
    std::cout << "Login: " << user << '\n';
}

int main(int argc, char* argv[])
{
    char user[N];
#ifdef KLEE
    klee_make_symbolic(&user[0], N * sizeof(char), "user");
#endif
    // user[N-1] = 0;
    login(user);
    return 0;
}
