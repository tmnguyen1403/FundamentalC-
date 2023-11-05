# Explicit specialization
Explicit specialization (also called full specialization) occurs when you provide a definition for a template instantiation with the full set of template arguments. The following can be fully specialized:

Function templates
Class templates
Variable templates (as of C++14)
Member functions, classes, and enumerations of a class template
Member function templates and class templates of a class or class template
Static data members of a class template

## Example
```
template <typename T, typename U>
void func(T a, U b)
{
   std::cout << "primary template\n";
}
template <>
void func(int a, int b)
{
   std::cout << "int-int specialization\n";
}
template <>
void func(int a, double b)
{
   std::cout << "int-double specialization\n";
}
func(1, 2);      // int-int specialization
func(1, 2.0);    // int-double specialization
func(1.0, 2.0);  // primary template
```
# Partial specialization

Partial specialization occurs when you specialize a primary template but only specify some of the template arguments. 
This means a partial specialization has both a template parameter list (which follows the template keyword) and a template argument list (which follows the template name). 
However, **only classes** can be partially specialized.

## Example
```
template <typename T, int S>
struct collection
{
   void operator()()
   { std::cout << "primary template\n"; }
};
template <typename T>
struct collection<T, 10>
{
   void operator()()
   { std::cout << "partial specialization <T, 10>\n"; }
};
template <int S>
struct collection<int, S>
{ 
   void operator()()
   { std::cout << "partial specialization <int, S>\n"; }
};
template <typename T, int S>
struct collection<T*, S>
{ 
   void operator()()
   { std::cout << "partial specialization <T*, S>\n"; }
};
```

Parameters in the template parameters list of the partial specialization cannot have default values.

The template parameters list implies an order of the arguments in the template arguments list, which is featured only in a partial specialization. This template arguments list of a partial specialization cannot be the same as the one implied by the template parameters list.

In the template argument list, you can only use identifiers for non-type template parameters. Expressions are not allowed in this context. This is demonstrated with the following example:
```
template <int A, int B> struct foo {};

template <int A> struct foo<A, A> {};     // OK

template <int A> struct foo<A, A + 1> {}; // error
```