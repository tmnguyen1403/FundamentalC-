#include <iostream>
#include<variant>
#include <cstdint>
#include <string>
//
struct A1{
    explicit A1(int a): a_{a}{};
    int a_;
};
struct A2{
    explicit A2(double a): a_{a}{};
    double a_;
};
struct A3{
    explicit A3(double a, uint8_t type): a_{a}, type_{type}{};
    double a_;
    uint8_t type_{0};
};
struct data{
    std::variant<A1,A2, A3> common;
    explicit data(A1 a1): common{a1} {
    }
    explicit data(A2 a2): common{a2} {
    }
    explicit data(A3 a3): common{a3} {
    }
    auto& get(){
        return common;
    }
};

//TODO:
/*
Write a processor that can handle both type and 
*/
template<class T>
class DataProcessor{
    public:
        void onNew(T& t) {
            std::cout << "Default DataProcessor\n";
            //if it is a textRp
        }
        void onUpdate(T& t) {

        }
};

template<>
class DataProcessor<data>{
    public:
        explicit DataProcessor<data>(): handle{10}{};
        void onNew(data& a) {
            std::cout << "data DataProcessor\n";
            auto f = [&a]<class T>(T& v){
                if constexpr(std::is_same_v<T, A1>){
                    std::cout <<"a1: " << v.a_ <<"\n";
                    a.common = A3 {v.a_+99.9, 1};;
                }
                else if constexpr(std::is_same_v<T,A2>) {
                    std::cout <<"a2: " << v.a_ <<"\n";
                    A3 a2{v.a_+500, 2};
                    a.common = A3 {v.a_+500, 2};
                }
            };
            std::visit(f, a.get());
            //if it is a textRp
        }
        void onUpdate(data& t) {
            
        }
    private:
        int handle;
};

template<class T, class U, class Z>
class B : public DataProcessor<U> {
public:
    void update(U& u) {
        std::cout << "default update\n";
        this->onNew(u);
    }
};

void title(std::string& s) {
    std::cout <<"title &s\n";
    std::string a = s;
}


void title(std::string&& s) {
    std::cout <<"title &&s\n";

    std::string a = std::move(s);
}

void title(int& s) {
    std::cout <<"title &s\n";
    int a = s;
}


void title(int&& s) {
    std::cout <<"title &&s\n";

   int a = std::move(s);
}

int main() {
    // B<int, float, char> b1;
    // b1.update();  // default update

    // B<int, double, char> b2;
    B<int, data, char> b3;

    A1 a1{100};
    A2 a2{20.5};
    data d1{a1};
    data d2{a2};

    auto f = []<class T>(T& x){
       
        if constexpr(std::is_same_v<T, A1>){
            std::cout <<"a1: " << x.a_ <<"\n";
        }
        else if constexpr(std::is_same_v<T,A2>) {
            std::cout <<"a2: " << x.a_ <<"\n";
        }
        else if constexpr(std::is_same_v<T,A3>){
            std::cout << "a3: " << x.a_ << "\n";
            std::cout << "type: " << static_cast<int>(x.type_) << "\n";
        }
    };

    std::cout << "d1\n";
    std::visit(f,d1.get());
    b3.update(d1);  // specialized update for double
     std::visit(f,d1.get());

    std::cout << "d2\n";
    std::visit(f,d2.get());
    b3.update(d2);  // specialized update for double
     std::visit(f,d2.get());
    
    //this work because const auto is deduce as const char[]
    // const auto s1{"hello"};
    // title(s1); 
    // title(std::move(s1)); 

    // const std::string s2{"hello"};
    // title(s2); 
    // title(std::move(s2)); 

    //not it does not work because type is deduced correctly
    // const auto s1{12};
    // title(s1); 
    // title(std::move(s1)); 

    // const std::string s2{"hello"};
    // title(s2); 
    // title(std::move(s2)); 
    
    // auto& da1 = d1.get();
    // auto& da2 = d2.get();
    // if (auto *pt1 = std::get_if<A1>(&da1)) {
    //     std::cout <<"a1" << pt1->a_ << std::endl;
    // }


    // std::visit(f,da1);
    // std::visit(f,da2);
    // std::visit(f,da1);
    // std::visit(f,da2);

    // da1 = d1.get();
    // da2 = d2.get();
    // std::cout << " next\n";
    // std::visit(f,da1);
    // std::visit(f,da2);
    // std::visit(f,da1);
    // std::visit(f,da2);
    // if (auto *pt2 = std::get_if<double>(&da2)) {
    //     std::cout <<"a2" << *pt2 << std::endl;
    // }


    return 0;
}