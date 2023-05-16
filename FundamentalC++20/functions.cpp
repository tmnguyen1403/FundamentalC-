#include <iostream>
// void f(int i);
// struct G {
//         void operator() (int i);
// }
// f(5); // function
// G g; g(5); // Functor

// lambda is callable object
#include <utility>

template <typename ... F> struct overload_set;

template <typename F1>
struct overload_set<F1> : public F1 {
    overload_set(F1&& f1) : F1(std::move(f1)) {}
    overload_set(const F1& f1) : F1(f1) {}
    using F1::operator();
};

template <typename F1, typename ... F>
struct overload_set<F1, F ...> : public F1, public overload_set<F ...> {
    overload_set(F1&& f1, F&& ... f) : 
        F1(std::move(f1)), overload_set<F ...>(std::forward<F>(f) ...) {}
    overload_set(const F1& f1, F&& ... f) :
        F1(f1), overload_set<F ...>(std::forward<F>(f) ...) {}
    using F1::operator();
};

template <typename ... F>
auto overload(F&& ... f) {
    return overload_set<F ...>(std::forward<F>(f) ...);
}

//Better solution
template <typename ... F>
struct better_set : public F ... {
    better_set(F && ... f) : F(std::forward<F>(f)) ... {}
    using F::operator() ...;
};

template <typename ...F>
auto betterload(F&& ... f) {
    return better_set<F ...>(std::forward<F>(f)...);
}

int main()
{
    int i = 5;
    double d = 7.3;
    char c = 'a';
    auto l = overload(
        [](int* i) { std::cout << "i= " << *i << std::endl;},
        [](double* d) { std::cout << "d = " << *d << std::endl;},
        [](char c) { std::cout << "c= " << c << std::endl;}
    );

     auto b = betterload(
        [](int* i) { std::cout << "i= " << *i << std::endl;},
        [](double* d) { std::cout << "d = " << *d << std::endl;},
        [](char c) { std::cout << "c= " << c << std::endl;}
    );
    l(&i);
    l(&d);
    l(c);
    std::cout << "Better set\n";
    b(&i);
    b(&d);
    b(c);
    return 0;
}