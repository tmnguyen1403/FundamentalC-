/*
Operator overloading is not automatic
+ must write operator functions
+ non-static member functions
+ can be defined as non-member functions

NOT ALLOWED TO BE OVERLOADED:
.(dot) member-selection
.* pointer-to-member
:: scope-resolution
:? conditional 

Default
+ assigment(=) - can be dangerous for classes with pointer members
+ address(&) - returns a pointer to an object
+ comma operator - eveluate the expression to its left then the expression to its right; returns the latter expression's value

Rules:
+ cannot change an operator's precedence
+ grouping cannot be changed
+ arity (the # of operands) cannot bec changed
+ cannot create new operator symbols
+ cannot change how an operator works on only fundamental-type values (cannot make + subtract two ints)

+ works only with custom-class objects or a mix of a custom-class object and a fundamental-type object
+ "() [] -> =" must be overloaded as member functions
*/

/*
Rule of Zero
_ C++ Core guidelines say design your classes such that the compiler can autogenerate:
+ copy constructor, copy assignment operator, move constructor, move assignment operator, destructor
_ To do that, composing each class'data using
+ fundamental-type members
+ objects of classes that do not require custom resource processing or that do it for you using RAII

Rule of Five:
+ Classes that manage their own resources should define the five special member functions

*/

/*
Moving does not move anything
+ Fundamental types still being copied
+ Original pointers are set to null
*/
#include <memory>
#include <iostream>
#include <initializer_list>
#include <span>

class MyArray final
{
    //overloaded stream extraction operator
    //friend std::istream& operator>> (std::);
    friend void swap(MyArray& a, MyArray& b) noexcept{
        
    }
    explicit MyArray(size_t size) : m_size{size}, m_ptr{std::make_unique<int[]>(size)}{
        std::cout << "MyArray(size_t) constructor\n";
    }
    
    //constructor of list of element for MyArray myArray{1,2,3,4,5}
    explicit MyArray(std::initializer_list<int> list) : m_size{list.size()}, m_ptr{std::make_unique<int[]>(list.size())}{
        std::copy(std::begin(list), std::end(list), m_ptr.get());
    }

    //copy constructor
    MyArray(const MyArray& origin): m_size{origin.size()}, m_ptr{std::make_unique<int[]>(origin.size())} {
        std::cout << "MyArray copy constructor\n";
        //span is iterable
        const std::span<const int> source{origin.m_ptr.get(), origin.size()};
        std::copy(std::begin(source), std::end(source), m_ptr.get());
    }


    //copy assignment operator: implemented with copy-and-swap idiom
    MyArray& operator=(const MyArray& right) {
        std::cout << "MyArray copy assignment operator\n";
        MyArray temp{right}; //invoke copy constructor, if failed to create temp, we haven't yet modified the original object
        swap(*this, temp); // exchange contents of this object and temp               
        return *this;
    }

    //move constructor
    MyArray(MyArray&& original) noexcept //move should not fail since object is already allocated
        : m_size(std::exchange(original.m_size, 0)),//swap the value of first and second, then return the value of the first argument
          m_ptr{std::move(original.m_ptr)} {
            std::cout << "MyArray move constructor";
    }

    //move assignment operator
    MyArray& operator=(MyArray&& right) noexcept {
        std::cout << "MyArray move assignment operator\n";
        if (this != &right) {
            m_size = std::exchange(right.m_size, 0);
            m_ptr = std::move(right.m_ptr);
        } //avoid self assignment
        return *this;
    }

    size_t size() const {
        return m_size;
    }

    private:
        size_t m_size;
        std::unique_ptr<int[]> m_ptr;
};

int main()
{
    return 0;
}