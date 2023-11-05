## ChatGPT Define

In C++, a "none-type template parameter" refers to a template parameter that is not a type. 
It is used to pass a value, a constant, or a reference to an object as a template argument.

 This feature was introduced in C++11 and allows the programmer to create templates that can be instantiated with non-type values, such as integers, pointers, references, or even other templates.

Here is an example of how a none-type template parameter can be use

## Example:

## 1. Passing a pointer to function parameter
```
struct device
{
   virtual void output() = 0;
   virtual ~device() {}
};
template <void (*action)()>
struct smart_device : device
{
   void output() override
   {
      (*action)();
   }
};
usage: 
void say_hello_in_english()
{
   std::cout << "Hello, world!\n";
}
void say_hello_in_spanish()
{
   std::cout << "Hola mundo!\n";
}
auto w1 =
   std::make_unique<smart_device<&say_hello_in_english>>();
w1->output();
auto w2 =
   std::make_unique<smart_device<&say_hello_in_spanish>>();
w2->output();
```

## 2. Pointer to member functions
```
template <typename Command, void (Command::*action)()>
struct smart_device : device
{
   smart_device(Command& command) : cmd(command) {}
   void output() override
   {
      (cmd.*action)();
   }
private:
   Command& cmd;
};
struct hello_command
{
   void say_hello_in_english()
   {
      std::cout << "Hello, world!\n";
   }
   void say_hello_in_spanish()
   {
      std::cout << "Hola mundo!\n";
   }
};
```
usage:

```
hello_command cmd;
auto w1 = std::make_unique<
   smart_device<hello_command, 
      &hello_command::say_hello_in_english>>(cmd);
w1->output();
auto w2 = std::make_unique<
   smart_device<hello_command, 
      &hello_command::say_hello_in_spanish>>(cmd);
w2->output();
```

## 3. Using auto
```
template <auto x>
struct foo
{ /* … */ };
This class template can be used as follows:

foo<42>   f1;  // foo<int>
foo<42.0> f2;  // foo<double> in C++20, error for older 
               // versions
foo<"42"> f3;  // error

// Not quite understand this
template<size_t N>
struct string_literal
{
   constexpr string_literal(const char(&str)[N])
   {
      std::copy_n(str, N, value);
   }
   char value[N];
};
However, the foo class template shown previously needs to be modified to use string_literal explicitly and not the auto specifier:

template <string_literal x>
struct foo
{
};
foo<"42"> f; 


//non-type template parameter pack
template<auto... x>
struct foo
{ /* ... */ };
foo<42, 42.0, false, 'x'> f;
```
