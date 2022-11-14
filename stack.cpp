#ifdef KLEE
#include <klee/klee.h>
#endif

#include <assert.h>

// C++ program to implement basic stack operations.
// Found here: https://www.softwaretestinghelp.com/stack-in-cpp/

#include <cstdlib>

#ifndef KLEE
#include <iostream>
#endif

constexpr auto MAX = 1000;

class Stack {

public:
    int top;
    int a[MAX]; // Maximum size of Stack

    Stack() { top = -1; }
    bool push(int x);
    int pop();
    bool isEmpty();
};

bool Stack::push(int x)
{
    if (top >= (MAX - 1)) {
        exit(1);
    } else {
        a[++top] = x;
        return true;
    }
}

int Stack::pop()
{
    if (top < 0) {
        return 0;
    } else {
        int x = a[top--];
        return x;
    }
}

bool Stack::isEmpty()
{
    return (top < 0);
}

// Driver program to test above functions
int main()
{
    class Stack s;
    int top;
    int e;
#ifdef KLEE
    klee_make_symbolic(&s, sizeof s, "s");
    klee_make_symbolic(&top, sizeof top, "top");
    klee_make_symbolic(&e, sizeof e, "e");
#endif
    s.top = abs(top) % (MAX + 1);
    if (s.top == MAX) {
        s.top = -1;
    }
#ifndef KLEE
    std::cout << s.top << std::endl;
#endif
    s.push(e);
    assert(e == s.pop());
    return 0;
}
