#include "wrapper.h"
#include <iostream>

template struct wrapper<int>;

void f()
{
    wrapper<int> a{42};
    std::cout << a.data << '\n';
}
