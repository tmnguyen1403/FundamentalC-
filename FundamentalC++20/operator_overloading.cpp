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
#include <string>
#include <sstream>
#include <algorithm>
#include <compare>
class Test final
{
    friend void swap(Test& a, Test& b) noexcept{
        std::swap(a.data, b.data);
    }
    public:
        explicit Test(double d): data{d}{}
        double getData() {
            return data;
        }
        auto operator<=>(const Test& t) const noexcept = default;
    private:
        double data{0.0};
};

class MyArray final
{
    friend MyArray operator+(const int& left , const MyArray& right) {
        MyArray result(right);
        return result + left;
        //return (right + left);
    }
    friend std::ostream& operator<<(std::ostream& os, const MyArray& data) {
        os << data.toString();
        return os;
    }
    friend void swap(MyArray& a, MyArray& b) noexcept{
        std::cout << "swapping\n";
        std::swap(a.m_size, b.m_size);
        a.m_ptr.swap(b.m_ptr);
        std::cout << "Done swapping\n";
    }
public:
    //overloaded stream extraction operator
    //friend std::istream& operator>> (std::);

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

    bool operator==(const MyArray& right) const noexcept {
        const std::span<const int> lhs{m_ptr.get(), m_size};
        const std::span<const int> rhs{right.m_ptr.get(), right.m_size};
        // right.m_ptr = nullptr; - I can access the private value but I cannot write to it
        return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
    }

    int& operator[](std::size_t index) {
        if (index >= m_size) {
            throw std::out_of_range{"Index out of range"};
        }
        return m_ptr[index];
    }

    MyArray operator+(const MyArray& right) {
        MyArray result(m_size);
        for (int count{0}; count < m_size; ++ count) {
            result.m_ptr[count] = m_ptr[count] + right.m_ptr[count];
        }
        return std::move(result);
    }

    MyArray operator+(const int& right) {
        MyArray result(m_size);
        for (int count{0}; count < m_size; ++ count) {
            result.m_ptr[count] = m_ptr[count] + right;
        }
        return std::move(result);
    }

   
    //
    void testAccessLevel(MyArray& other) {
        const std::span<const int> t{other.m_ptr.get(), other.m_size};
        other.m_size = 20;
    }

    ~MyArray() = default;

    size_t size() const noexcept {
        return m_size;
    }

    std::string toString() const {
        const std::span<const int> items{m_ptr.get(), m_size};
        std::ostringstream output;
        output << "{";

        for (std::size_t count{0}; const auto& item: items) {
            ++count;
            output << item << (count < m_size ? ", " : "");
        }
        output <<"}";
        return output.str();
    }

private:
    std::size_t m_size;
    std::unique_ptr<int[]> m_ptr;
};



int main()
{
    MyArray a1{1,2,3,4,5};
    MyArray a2{1,2,3,4,5};
    MyArray a3{1,2,3};
    std::cout << a1.toString() << std::endl;
    std::cout << std::boolalpha << "a1 == a2" <<  (a1 == a2) << std::endl;
    std::cout << std::boolalpha << "a1 == a3" << (a1 == a3) << std::endl;
    a1.testAccessLevel(a2);
    std::cout << a2.size() << std::endl;
    std::cout << "a1[3] = " << a1[3] << std::endl;
    std::cout << (a1 + a2).toString() << std::endl;
     std::cout << (a1 + 10).toString() << std::endl;
    std::cout << (10 + a1).toString() << std::endl;
    std::cout << (10 + a1 + a2 + a3 + 24).toString() << std::endl;
    
    std::cout << "a1: " <<  a1 << std::endl;
    std::cout << "a3:" << a3 << std::endl;
    std::cout << "swap(a1,a3)\n";

    swap(a1, a3);
    std::cout << "a1: " <<  a1 << std::endl;
    std::cout << "a3:" << a3 << std::endl;

    Test t1{12.0}, t2{24.0};
    std::cout << "t1: " << t1.getData() << std::endl;
    std::cout << "t2: " << t2.getData() << std::endl;
    std::cout << "t1 < t2: " << (t1 < t2) << std::endl;
    std::cout << "swap(t1,t2)\n";
    swap(t1,t2);
    std::cout << "t1: " << t1.getData() << std::endl;
    std::cout << "t2: " << t2.getData() << std::endl;
    std::cout << "t1 < t2: " << (t1 < t2) << std::endl;
    if ((t1 <=>t2) == 0) {
        std::cout << "t1 = t2\n";
    }
    if ((t1 <=>t2) < 0) {
        std::cout << "t1 < t2\n";
    }
    if ((t1 <=>t2) > 0) {
        std::cout << "t1 > t2\n";
    }
    return 0;

}