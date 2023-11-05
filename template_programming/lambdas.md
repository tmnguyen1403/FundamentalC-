# Generic lambda and template lambda
```
auto l1 = [](int a) {return a + a; };  // C++11, regular 
                                       // lambda
auto l2 = [](auto a) {return a + a; }; // C++14, generic 
                                       // lambda
auto l3 = []<typename T>(T a) 
          { return a + a; };   // C++20, template lambda
auto v1 = l1(42);                      // OK
auto v2 = l1(42.0);                    // warning
auto v3 = l1(std::string{ "42" });     // error
auto v5 = l2(42);                      // OK
auto v6 = l2(42.0);                    // OK
auto v7 = l2(std::string{"42"});       // OK
auto v8 = l3(42);                      // OK
auto v9 = l3(42.0);                    // OK
auto v10 = l3(std::string{ "42" });    // OK

```
Here, we have three different lambdas: l1 is a regular lambda, l2 is a generic lambda, as at least one of the parameters is defined with the auto specifier, and l3 is a template lambda, defined with the template syntax but without the use of the template keyword.

We can invoke l1 with an integer; we can also invoke it with a double, but this time the compiler will produce a warning about the possible loss of data. 

However, trying to invoke it with a string argument will produce a compile error, because std::string cannot be converted to int. 

On the other hand, l2 is a generic lambda. The compiler proceeds to instantiate specializations of it for all the types of the arguments it's invoked with, in this example int, double, and std::string. The following snippet shows how the generated function object may look, at least conceptually:

## Generic lambda
```
auto factorial = [](auto f, int const n) {
   if (n < 2) return 1;
   else return n * f(f, n - 1);
};
factorial(factorial, 5);
```
A generic lambda is a function object with a template function-call operator. The first argument, specified with auto, can be anything, **including the lambda itself**. Therefore, the compiler will provide a full explicit specialization of the call operator for the type of the generated class.