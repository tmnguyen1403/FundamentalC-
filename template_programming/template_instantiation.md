# Implicit instantiation
Implicit instantiation occurs when the compiler generates definitions based on the use of templates and when no explicit instantiation is present.

Implicitly instantiated templates are defined in the same namespace as the template. However, the way compilers create definitions from templates may diffe

### Example
```
template <typename T>
struct foo
{
  void f() {}
};
int main()
{
  foo<int> x;
}
Here, we have a class template called foo with a member function f. In main, we define a variable of the type foo<int> but do not use any of its members. Because it encounters this use of foo, the compiler implicitly defines a specialization of foo for the int type. If you use cppinsights.io, which runs in Clang, you will see the following code:

template<>
struct foo<int>
{
  inline void f();
};

Because the function f is not invoked in our code, it is only declared but not defined. Should we add a call f in main, the specialization would change as follows:

template<>
struct foo<int>
{
  inline void f() { }
};
```
## Implicit of class templates
For class templates, implicit instantiation occurs when the user code refers to a template in a context when a complete type is required or when the completeness of the type affects the code.

The typical example of such a context is when an object of such a type is constructed. However, this is not the case when declaring pointers to a class template.

### Example
```
template <typename T>
struct foo
{
  void f() {}
  void g() {}
};
int main()
{
  foo<int>* p;
  foo<int> x;
  foo<double>* q;
}
```
In this snippet, we use the same foo class template from the previous examples, and we declare several variables: p which is a pointer to foo<int>, x which is a foo<int>, and q which is a pointer to foo<double>. The compiler is required to instantiate only foo<int> at this point because of the declaration of x. Now, let's consider some invocations of the member functions f and g as follows:
```
int main()
{
  foo<int>* p;
  foo<int> x;
  foo<double>* q;
  x.f();
  q->g();
}
```
With these changes, the compiler is required to instantiate the following:

foo<int> when the x variable is declared
foo<int>::f() when the x.f() call occurs
foo<double> and foo<double>::g() when the q->g() call occurs.

## Class template with static members
When a class template contains static members, those members are not implicitly instantiated when the compiler implicitly instantiates the class template but only when the compiler needs their definition. 

On the other hand, every specialization of a class template has its own copy of static members as exemplified in the following snippet:
```
template <typename T>
struct foo
{
   static T data;
};
template <typename T> T foo<T>::data = 0;
int main()
{
   foo<int> a;
   foo<double> b;
   foo<double> c;
   std::cout << a.data << '\n'; // 0
   std::cout << b.data << '\n'; // 0
   std::cout << c.data << '\n'; // 0
   b.data = 42;
   std::cout << a.data << '\n'; // 0
   std::cout << b.data << '\n'; // 42
   std::cout << c.data << '\n'; // 42
}
```

# Explicit instantiation efinition
As a user, you can explicitly tell the compiler to instantiate a class template or a function template. 
This is called explicit instantiation and it has two forms: explicit instantiation definition and explicit instantiation declaration. We will discuss them in this order.
```
The syntax for class templates is as follows:
template class-key template-name <argument-list>

The syntax for function templates is as follows:
template return-type name<argument-list>(parameter-list);

template return-type name(parameter-list);
```
### Example
*Explicit instantiation for class template*
```
namespace ns
{
   template <typename T>
   struct wrapper
   {
      T value;
   };
   template struct wrapper<int>;       // [1]
}
template struct ns::wrapper<double>;   // [2]
int main() {}
```
In this snippet, wrapper<T> is a class template defined in the ns namespace. 

The statements marked with [1] and [2] in the code are both representing an explicit instantiation definition, for wrapper<int> and wrapper<double> respectively. 

An explicit instantiation definition can only appear in the same namespace as the template it refers to (as in [1]) to or it must be fully qualified (as in [2]). We can write similar explicit template definitions for a function template

*Explicit instantiation for function template*
```
namespace ns
{
   template <typename T>
   T add(T const a, T const b)
   {
      return a + b;
   }
   template int add(int, int);           // [1]
}
template double ns::add(double, double); // [2]
int main() { }
```
### When to use
```
Having seen what explicit instantiation definition is and how it works, the question that arises is when is it useful. Why would you tell the compiler to generate instantiation from a template? The answer is that it helps distribute libraries, reduce build times, and executable sizes. 
If you are building a library that you want to distribute as a .lib file and that library uses templates, the template definitions that are not instantiated are not put into the library. But that leads to increased build times of your user code every time you use the library. 
By forcing instantiations of templates in the library, those definitions are put into the object files and the .lib file you are distributing. As a result, your user code only needs to be linked to those available functions in the library file. This is what the Microsoft MSVC CRT libraries do for all the stream, locale, and string classes. The libstdc++ library does the same for string classes and others.
```

# Explicit instantiation declaration
An explicit instantiation declaration (available with C++11) is the way you can tell the compiler that the definition of a template instantiation is found in a different translation unit and that a new definition should not be generated. The syntax is the same as for explicit instantiation definitions except that the keyword **extern** is used in front of the declaration:

```
The syntax for class templates is as follows:
extern template class-key template-name <argument-list>

The syntax for function templates is as follows:
extern template return-type name<argument-list>(parameter-list);

extern template return-type name(parameter-list);
```
If you provide an explicit instantiation declaration but no instantiation definition exists in any translation unit of the program, then the result is a compiler warning and a linker error. The technique is to declare an explicit template instantiation in one source file and explicit template declarations in the remaining ones. This will reduce both compilation times and object file sizes.

```

// wrapper.h
template <typename T>
struct wrapper
{
   T data;
}; 
extern template struct wrapper<int>;   // [1] explicit instantiation declaration

// source1.cpp
#include "wrapper.h"
#include <iostream>
template struct wrapper<int>;          // [2] explicit instantiation definition
void f()
{
   ext::wrapper<int> a{ 42 };
   std::cout << a.data << '\n';
}

// source2.cpp
#include "wrapper.h"
#include <iostream>
void g()
{
   wrapper<int> a{ 100 };
   std::cout << a.data << '\n';
}
// main.cpp
#include "wrapper.h"
int main()
{
   wrapper<int> a{ 0 };
}
```