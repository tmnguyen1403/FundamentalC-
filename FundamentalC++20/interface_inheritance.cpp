#include <string>

class CompensationModel
{
    public:
        virtual ~CompensationModel() = default;
        virtual double earnings() const = 0;
        virtual std::string toString() const = 0;
};

class Salaried final : public CompensationModel {
    public:
        explicit Salaried(double salary);
        double earnings() const override;
        std::string toString() const override;
    private:
        double m_salary{0.0};
};

class Commission final : public CompensationModel {
    public:
        explicit Commission(double grossSales, double commissionRate);
        double earnings() const override;
        std::string toString() const override;
    private:
        double m_grossSales{0.0};
        double m_salary{0.0};
};

class Employee final {
    public:
        //dependency injection by using constructor 
        Employee(std::string_view name, CompensationModel* modelptr);
        //property injection
        void setCompensationModel(CompensationModel *modelptr);
        double earnings() const;
        std::string toString() const;
    private:
        std::string m_name{};
        CompensationModel *m_modelptr{};
};
