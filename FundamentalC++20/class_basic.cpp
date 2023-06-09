#include <iostream>
#include <string>
#include <string_view>

class Bank
{
    public:
    Bank(std::string_view bname){
        std::cout << "Bank constructor is called\n";
        name = bname;
        counter += 12; //increase static value inside the constructor
    }
    ~Bank(){
        std::cout << "Bank destructor is called\n";

    }
    private:
        std::string name;
        inline static int counter{0}; //inline keyword allows to initiazied the static variable inline
        static int no_inline; //error: non-const static data member must be initialized out of line
};
int Bank::no_inline = 12;
/*
Class scope
+ Account account{}; //an account object
+ Account& ref{account}; //ref refers to an Account object
+ Account* ptr{&account}; // ptr points to an Account object
*/
class Account 
{
    //friendship - allow the free method to access the private data of the class
    /*
    + Friendship is granted, not taken.
    + Friendship is not symmetric - A is friend of B but B might/might not friend of A
    + Friendshuip is not transitive - A friend B, B friend C, A is not friend C.
    
    */
    friend void setBalance(Account& acc, double value);
public:

    //default constructor

    //explicit - the compiler will not call the constructor automatically
    //good practice - declare single argument constructor as explicit
    //multiple argument constructors are not called implicitly by the compiler, so explicit might not be necessary
    explicit Account(std::string_view name="", double balance=0.0) : m_name{name}, bank{name} //member initializer
    {
        std::cout << "Account constructor body is called\n";
        if (balance > 0.0){
            m_balance = balance;
        }
    }
    ~Account() {
        std::cout << "Account destructor is called\n";
    }

    void deposit(double amount) {
        if (amount > 0.0) {
            m_balance += amount;
        }
    }

    double getBalance() const {
        return m_balance;
    }

    void setArray() {
        a[0] = a[0]+ 200;
    }

    const int* getArray() {
        return a;
    }

    void setName(std::string_view name) {
        m_name = name;
    }

    //return a const reference - caller cannot modify the name
    //const at the end - the function does not modify class data members
    //allowing the function to be called if a const object is created 
    const std::string& getName() const {
        return m_name;
    }
private:
    std::string m_name;
    double m_balance{0.0}; //in-class initiliazer - recommended to provide default initial value
    int a[5]{};
    Bank bank; 
};

void setBalance(Account& acc, double value){
    acc.m_balance = value;
}

struct DesignatedInitilizer
{
    int first;
    int last;

};
int main()
{
    DesignatedInitilizer di{.first{100}, .last{200}};
    std::cout << di.first << " " << di.last << std::endl;
    
    Account a0{};
    a0.setArray();
    setBalance(a0, 99.99);
    std::cout << "setBalance for a0 using friend function - balance: " << a0.getBalance() << std::endl;

    Account at{};
    at = a0;
    std::cout <<"Check default assignment operator to see if it does shallow or deep copy with the array data member. It is deep copy:\n";
    const int* ptr1 = a0.getArray();
    const int* ptr2 = at.getArray();

    a0.setArray();

    std::cout << "a0.a[0]: " << *ptr1 << std::endl;
    std::cout << "at.a[0]" << *ptr2 << std::endl;  
    std::cout << "a0.a[0] address: " << &(*ptr1) << std::endl;
    std::cout << "at.a[0] address" << &(*ptr2) << std::endl;  

    Account a1{"Mike", 100.0};
    a1.setName("Peter");

    std::cout << "a1 name: " << a1.getName() << std::endl;
    std::cout << "balance: " << a1.getBalance() << std::endl;
    std::cout << "deposit 400\n"; 
    a1.deposit(400);
    std::cout << "balance: " << a1.getBalance() << std::endl;
    
    const Account a2{"Loki", -1000};
    //a2.setName("Perter"); -- error due to const keyword
    std::cout << "a2 name: " << a2.getName() << std::endl; // without const, getName will not be callable
    std::cout << "balance: " << a2.getBalance() << std::endl;

    return 0;

}