/*
4 ways to pass a pointer to a function
+ a nonconstant pointer to nonconstant data
+ a nonconstant pointer to constant data
+ a constant pointer to nonconstant data (cannot change where pointer point to, but can modify the data)
+ a constant pointer to constant data
*/

int main() {
    int y{1};
    const int* ptr1{&y}; //pointer to an integer constant
    *ptr1 = 100; //cannot modify the value
    int x{2};
    int * const ptrX{&x}; //const pointer must be initialized
    *ptrX = 10;
    ptrX = &y; //not allowed since the pointer is constant

    const int* const ptrC{&x};
    *ptrC = 5;
    ptrC = &y;
}