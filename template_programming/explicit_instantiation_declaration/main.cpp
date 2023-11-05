#include "wrapper.h"
void f();
void g();
int main()
{
    wrapper<int> a{0};
    f();
    g();
}