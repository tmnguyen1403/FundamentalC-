/*
Old design pattern
+ allocate dynamic memory --> assign the address of that memory to a pointer
--> use the pointer to manipulate the memory --> deallocate the memory when it's no longer needed
If an exception occurs before deallocation --> memory leak

Solution:
RAII - Resource Acquitision Is Initilization
+ create local object and acquire the resource during construction
+ use the object
+ when the object goes out of scope, destructor called automatically to release the resource

Smart pointers:
#include <memory>
+ unique_ptr - dynamically allocated object can belong to only one unique_ptr at at time
+ shared_ptr - can belong to many pointers, the object is destroyed when the last pointer goes out of scope
+ weak_ptr - if a weak_ptr is the last pointer pointing to an object of a shared_ptr, it does not prevent the object to be deallocated
*/
/*
unique_ptr Ownership
+ assigning one unique_ptr to another transfers ownership - also when passing one unique_ptr to another's constructor
This also occurs if passing by value, return the value from function.
+ Last unique_ptr that owns the dynamic memory will delete it

*/
#include <iostream>
#include <memory>

class Integer {
public:
    Integer(int i) : value{i} {
        std::cout << "Constructor for Integer " << value << std::endl;
    }

    ~Integer() {
        std::cout << "Destructor for Integer " << value << std::endl; 
    }

    int getValue() const {return value;}
private:
    int value{0};
};

void testUniquePtrOwnership(std::unique_ptr<Integer> a) {
    std::cout << "a is going to be deleted after the function call??\n"; 
}

int main() {
    std::cout << "creating a unique_ptr object\n";
    auto ptr{std::make_unique<Integer>(20)};
    std::cout << "Integer value: " << ptr->getValue() << std::endl;
    testUniquePtrOwnership(std::move(ptr));
    std::cout << "End Main!!\n";

    /*
    Use with built-in array
    auto ptr{std::make_unique<int[]>(10)};
    
    */
    return 0;
}