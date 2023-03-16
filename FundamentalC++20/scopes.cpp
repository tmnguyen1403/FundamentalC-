#include <iostream>
/*
block scope:
global namespace scope: 
. identifier declared outside any function or class
. known from the point at which it's declared until the end of the file
. function definitions, function prototypes, class definitions, global variables
*/
void staticLocal();

int main() {
    staticLocal();
    staticLocal();
    staticLocal();
    return 0;
}

void staticLocal() {
    /*
    * When the function is first called, x is initilized to 100
    * Its lifetime is then maintained in memory. Therefore, repeated call to staticLocal will increase the value of x
    */
   
    static int x{100};
    std::cout << "calling staticLocal\n";
    std::cout << "value x: " << x++ << std::endl; 
}