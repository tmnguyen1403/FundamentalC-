#include <iostream>
#include <exception>

class Failed
{
    public:
    Failed(){
        std::cout << "Failed class\n";
        throw std::runtime_error("Failed constructor failed");
    }
};

class HandleFailed
{
    public:
    HandleFailed(Failed f) try : f_{f} {
        std::cout << "HandleFailed constructor class\n";

    } catch (const std::runtime_error& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
    private:
    Failed f_; 
};

int main()
{
    try{
     HandleFailed h{Failed{}};

    } catch(const std::runtime_error& e) {
        std::cout << "caught in main: " << e.what() << std::endl;
    }
    return 0;
}