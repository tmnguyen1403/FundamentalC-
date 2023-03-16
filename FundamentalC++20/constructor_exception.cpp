#include <iostream>
#include <exception>

class Failed
{
    public:
    explicit Failed(){
        std::cout << "Failed constructor class\n";
        throw std::runtime_error("Failed constructor failed");
    }
    explicit Failed(int value){
        std::cout << "Failed constructor class\n";
        throw std::runtime_error("Failed constructor failed");
    }
    private:
    int i{};
};

class HandleFailed
{
    public:
    explicit HandleFailed(Failed f) try : f_{f} {
        std::cout << "HandleFailed constructor class\n";

    } catch (const std::runtime_error& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
    explicit HandleFailed(int value) try : f_{value} {
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
     
     std::cout << "\nThe below execution generates exception aught in HandleFailed constructor first, then rethrow\n";
     try{
     HandleFailed h{123};

    } catch(const std::runtime_error& e) {
        std::cout << "caught in main: " << e.what() << std::endl;
    }
    return 0;
}