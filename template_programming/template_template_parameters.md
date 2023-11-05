## Definition from book
Template template parameters refers to a category of template parameters that are themselves templates. These can be specified similarly to type template parameters, with or without a name, with or without a default value, and as a parameter pack with or without a name.

As of C++17, both the keywords class and typename can be used to introduce a template template parameter. Prior to this version, only the class keyword could be used

## Example 
## 1.
```
template <typename T>
class simple_wrapper
{
public:
   T value;
};
template <typename T>
class fancy_wrapper
{
public:
   fancy_wrapper(T const v) :value(v)
   {
   }
   T const& get() const { return value; }
   template <typename U>
   U as() const
   {
      return static_cast<U>(value);
   }
private:
   T value;
};

//W is a template template parameter
template <typename T, typename U, 
          template<typename> typename W = fancy_wrapper>
class wrapping_pair
{
public:
   wrapping_pair(T const a, U const b) :
      item1(a), item2(b)
   {
   }
   W<T> item1;
   W<U> item2;
};
Usage:
wrapping_pair<int, double> p1(42, 42.0);
std::cout << p1.item1.get() << ' '
          << p1.item2.get() << '\n';
wrapping_pair<int, double, simple_wrapper> p2(42, 42.0);
std::cout << p2.item1.value << ' '
          << p2.item2.value << '\n';
```