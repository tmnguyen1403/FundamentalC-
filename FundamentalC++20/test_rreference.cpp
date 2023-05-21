#include <iostream>
#include <memory>
#include <type_traits>

class A{
public:
    explicit A(int a): a_{a}{};

    template <class T>
    void copy(T&& t) {
        std::cout << "Test T\n";
        //This is just reference, I get it now, this is very confusing at first
        T b(std::forward<T>(t));
        b.hello();
        T b1{std::forward<T>(t)};
        b1.hello();
    }

private:
    int a_;
};

struct B {
    static int id;
    explicit B(){++id; id_=id; std::cout <<"Calling B constructor" << id << std::endl;};
    B(B& source) {
        std::cout << "Calling B copy constructor\n";
        id_ = source.id_;
    }
    B(const B& source) {
        std::cout << "Calling B NOT copy constructor\n";
        id_ = source.id_;
    }

    void hello() {
        std::cout << "B-id: " << id_ <<" " << &(*this) << std::endl;
    }
    int id_;
};
int B::id = 0;

class X {
public:
    X(){std::cout << "Calling X constructor\n";};
    X(X& other){
        std::cout << "Calling X copy constructor\n";
    };
    X(X&& other){
        std::cout << "Calling X move constructor\n";
    };
};
template <typename T>

auto factory(T&& t) {
    // T t2{std::forward<T>(t)};
    using U = typename std::remove_reference_t<T>;
    return std::shared_ptr<U>(new U(std::forward<T>(t)));
}
template<class S>
S&& forward(typename std::remove_reference<S>::type& a) noexcept
{
    std::cout << "original\n";
  return static_cast<S&&>(a);
}


template<class S>
S&& forward(S& a) noexcept
{
    std::cout << "not original\n";
  return static_cast<S&&>(a);
}
int main() {
    
    X x;
    factory(x);
    // A a{10};
    // B b{};
    // b.hello();
    // a.copy(b);
    forward(x);
    forward<X>(x);
    return 0;
}



/*
Reference collapsing rules:
A& & becomes A&
A& && becomes A&
A&& & becomes A&
A&& && becomes A&&

Secondly, there is a special template argument deduction rule for function templates that take an argument by rvalue reference to a template argument:
template<typename T>
void foo(T&&);
Here, the following apply:
When foo is called on an lvalue of type A, then T resolves to A& and hence, by the reference collapsing rules above, the argument type effectively becomes A&.
When foo is called on an rvalue of type A, then T resolves to A, and hence the argument type becomes A&&.

By overloading a function like this:
void foo(X& x); // lvalue reference overload
void foo(X&& x); // rvalue reference overload
you can branch at compile time on the condition "is foo being called on an lvalue or an rvalue?" The primary (and for all practical purposes, the only) application of that is to overload the copy constructor and copy assignment operator of a class for the sake of implementing move semantics. If and when you do that, make sure to pay attention to exception handling, and use the new noexcept keyword as much as you can.
 
std::move turns its argument into an rvalue.
 
std::forward allows you to achieve perfect forwarding if you use it exactly as shown in the factory function example in Section 8.
*/
