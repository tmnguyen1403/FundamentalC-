/*
Compile-time polymorphism
. compiler generates class template specialization
. defined entired class in the header file
. defined function inside the header makes it easier to reducate template<typename T> above each function (if defined in another file)
*/


#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <concepts>

// Traditional Function Template
// template <typename T>
// void printContainer(const T& items) {
//     for (const auto& item: items) {
//         std::cout << item << " ";
//     }
//     std::cout<<std::endl;
// }

/*
Abbreviated function templates leveraging auto
*/
void printContainer(const auto& items) {
    for (const auto& item: items) {
        std::cout << item << " ";
    }
    std::cout<<std::endl;
}

/*
Constrained function templates
*/
template<typename T>
    requires std::integral<T> || std::floating_point<T>
T multiply(T first, T second) { return first * second;}

/*
Custom concept
*/
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<typename T>
    requires Numeric<T>
T add(T a, T b) { return a + b;}

//trailing syntax
/*
1. used in class member function due to lack of template header
2. Name of parameter is being used in the concept, so the name has to be in scope for checking
*/
template<typename T>
T minus(T a, T b) requires Numeric<T> {return a - b;}

//can eliminate the typename with the concepter
template<Numeric T> 
T divide(T a, T b) {return a/b;}

//abbreviated function template with constrained auto
auto multiply(Numeric auto first, Numeric auto second) {
    return first * second; 
}

class A{
public:
    void hello(){std::cout << "Hello A: everyone\n";}
};
class B{
public:

};
class C{
public:
    void hello(std::string a, std::string b){std::cout << "Hello " << a << " " << b << std::endl;}
};

template<typename T>
concept Hello = requires(T t) {
    t.hello();
};

template<typename F, class T, typename ... Args>
concept HelloArg = requires(F&& f, T&& t, Args&&... args) {
    std::is_invocable_v<F, T, Args...>; 
};

template<Hello T>
void handle(T t) {
    //static_assert helps better error message at compile time
    //the second argument can be a custom message if failed
    static_assert(Hello<T>, "Not hello T"); //evalute at compile time, compile if this is True
    t.hello();
}

template<typename F, typename T, typename... Args>
    requires HelloArg<F, T, Args...>
void handle(F&& f, T&& t, Args&&... args) {
    std::invoke(std::forward<F>(f), std::forward<T>(t), std::forward<Args>(args)...);
}

template<typename T>
void handle(T t) {
    std::cout << "Handle nothing\n";
    return;
}

int main() {
    std::array ints{1,2,3,4,5};
    /*
Templated lambda
*/
    auto r = []<typename T>(T total, T value){ return total + value;};
    std::cout << "templated lambda value: " << r(1,2) << std::endl;
    printContainer(ints);
    std::cout << "2 * 5 = " << multiply(2,5) << std::endl;
    std::cout << "2.2 * 5.3 = " << multiply(2.2,5.2) << std::endl;
    //std::cout << "a * b = " << multiply("a","b") << std::endl; - compiler error
    std::cout << "Custom Concept Add: 1 + 3 = " << add(1,3) << std::endl; 
    std::cout << "Custom Concept Add: 1.2 + 3.5 = " << add(1.2,3.5) << std::endl; 

    std::cout << "Custom Concept Trailing syntax Minus: 1.2 - 3.5 = " << minus(1.2,3.5) << std::endl; 
    std::cout << "Using concept instead of typename: 1.2 / 3.5 = " << divide(1.2,3.5) << std::endl; 

    std::cout << "Mix type multiply: 1 * 3.2 = " << multiply(1, 3.2) << std::endl;

    //
    std::cout << "Invocable object\n" << std::boolalpha;
    std::cout << Hello<A> << std::endl;
    std::cout << Hello<B> << std::endl;

    A a{};
    B b{};
    C c{};
    handle(a);
    handle(b);
    handle(&C::hello,c,"a", "b");
    handle(&C::hello,c,"cc", "dd");
    c.hello("after", "after");
}

/*
std::forward - ChatGPT

In C++, std::forward is a utility function that is used to implement perfect forwarding, which is a technique that allows you to preserve the value category of a function argument when it is passed along to another function.

When you pass an argument to a function, its value category (i.e., whether it is an lvalue or an rvalue) is determined based on how it is initialized. An lvalue is a named object that has a persistent address, while an rvalue is a temporary object that is created by the compiler and has no persistent address.

If you pass an lvalue argument to a function that takes it by value or an rvalue reference, the argument will be copied or moved, respectively, and the resulting parameter will be an lvalue. If you pass an rvalue argument to a function that takes it by value or an rvalue reference, the argument will be moved, and the resulting parameter will be an rvalue.

However, sometimes you want to pass an argument to another function in such a way that its value category is preserved. This is where perfect forwarding comes in. If you have a function template that takes a forwarding reference (i.e., an rvalue reference to a template parameter of the form T&&), you can use std::forward to pass the argument along to another function in such a way that its value category is preserve

#include <iostream>

void foo(int& x) {
    std::cout << "lvalue reference" << std::endl;
}

void foo(int&& x) {
    std::cout << "rvalue reference" << std::endl;
}

template<typename T>
void bar(T&& x) {
    foo(std::forward<T>(x));
}

int main() {
    int a = 42;
    bar(a); // lvalue reference
    bar(42); // rvalue reference
}
*/

/*std::invoke - ChatGPT

std::invoke is a utility function provided by the C++ Standard Library that provides a uniform syntax for calling functions and function-like objects, such as function pointers, member function pointers, and functors.

The syntax for calling these different types of callable objects can be quite different. For example, calling a member function requires an instance of the class to call the function on, while calling a free function does not. Similarly, calling a functor requires constructing an instance of the functor, while calling a function pointer does not.

std::invoke provides a uniform syntax for calling all of these different types of callable objects. It takes two arguments: the callable object and the arguments to be passed to the callable object. The syntax is as follows:

c++
Copy code
template <typename F, typename... Args>
decltype(auto) invoke(F&& f, Args&&... args);
The first argument, f, is the callable object to be invoked. The remaining arguments, args, are the arguments to be passed to the callable object.

The return type of std::invoke depends on the type of the callable object and the arguments passed to it. It is specified using decltype(auto), which means that the return type will be deduced based on the type of the expression f(std::forward<Args>(args)...).

Here are some examples of how std::invoke can be used:

c++
Copy code
#include <iostream>
#include <functional>

void foo(int x, int y) {
    std::cout << "x + y = " << x + y << std::endl;
}

class Bar {
public:
    void baz(int x, int y) const {
        std::cout << "x * y = " << x * y << std::endl;
    }
};

int main() {
    // Call a free function
    std::invoke(foo, 2, 3);

    // Call a member function on an object
    Bar bar;
    std::invoke(&Bar::baz, bar, 2, 3);

    // Call a member function on a pointer to an object
    Bar* bar_ptr = &bar;
    std::invoke(&Bar::baz, bar_ptr, 2, 3);

    // Call a functor
    std::function<void(int, int)> qux = [](int x, int y) {
        std::cout << "x - y = " << x - y << std::endl;
    };
    std::invoke(qux, 2, 3);
}
In this example, we define a free function foo and a class Bar with a member function baz. We then call std::invoke to invoke foo with the arguments 2 and 3, call baz on an instance of Bar with the arguments 2 and 3, call baz on a pointer to an instance of Bar with the arguments 2 and 3, and call a functor with the arguments 2 and 3. In all cases, the correct syntax for calling the callable object is abstracted away by std::invoke.

*/

