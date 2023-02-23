/*
. std::variant stores one object at a time of any type specified when you create the std::variant
. call functions on the objects in a std::variant object using the std::visit function
. it is a type-safe union
. Cons: needs to know object types in advance,

. duck-typing: being able to invoke same functions of unrelated classes without inheritance - eliminate type coupling
*/
#include <iostream>
#include <string>
#include <variant>
// no inheritance
class Salaried{
    public:
        explicit Salaried(double salary): m_salary{salary}{};
        double earnings() const {return m_salary;};
        std::string toString() const {return "salaried";};
    private:
        double m_salary{0.0};
};

class Commission {
    public:
        Commission(double grossSales, double commissionRate): m_grossSales{grossSales}, m_commissionRate{commissionRate}{};
        double earnings() const {return m_grossSales * m_commissionRate;};
        std::string toString() const {return "commission";};
    private:
        double m_grossSales{0.0};
        double m_commissionRate{0.0};
};

using CompensationModel = std::variant<Commission, Salaried>;
class Employee final {
    public:
        //dependency injection by using constructor 
        Employee(std::string_view name, CompensationModel model):m_name{name}, m_model{model} {};
        //property injection
        void setCompensationModel(CompensationModel model){
            m_model = model;
        };
        double earnings() const{ 
            
            auto getEarnings = [](const auto& model){return model.earnings();};
            //the m_model is used as the argument in the lambda function call,
            //the return value of the lambda function becomes the return value of std::visit
            return std::visit(getEarnings, m_model);
        };
        std::string toString() const {
            auto getString = [](const auto&model) {return model.toString();};
            return m_name + std::visit(getString, m_model);
        };
    private:
        std::string m_name{};
        CompensationModel m_model;
};

int main()
{
    Salaried salaried{20.0};
    Commission commission{20.0, 30.0};
    Employee salariedEmployee{"Zeo P ", salaried};
    Employee commissionEmployee{"Luke V ", commission};

    std::cout << salariedEmployee.toString() << " - salary: " << salariedEmployee.earnings() << std::endl;
    std::cout << commissionEmployee.toString() << " - salary: " << commissionEmployee.earnings() << std::endl;

    return 0;
}