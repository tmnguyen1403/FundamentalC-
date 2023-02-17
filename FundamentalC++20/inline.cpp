/*
inline:
Behaviour:
. expand function definition where it's called
Pros:
. removes the overhead of the function call
Cons:
. increase file size
. files use inline function has to be recompiled if the inline function changes
Ref:
https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-inline

*/

#include <iostream>

inline void inline_hello() {
    std::cout << "Hello, I am an linline function\n";
}
int main() {
    inline_hello();
    inline_hello();
}