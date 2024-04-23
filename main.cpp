#include <iostream>
#include <deque>
#include <fstream>
#include <string>
#include <set>
#include <unordered_set>

class Employee {
public:
    std::string name;
    std::string hire_date;
    std::string position;
    double base_salary;

    Employee() : name(""), hire_date(""), position(""), base_salary(0.0) {}

    Employee(const std::string& n, const std::string& h, const std::string& p, double s)
        : name(n), hire_date(h), position(p), base_salary(s) {}

    friend std::ostream& operator<<(std::ostream& os, const Employee& e) {
        os << e.name << ": " << e.hire_date << ", " << e.position << ", " << e.base_salary << "$";
        return os;
    }

    bool operator<(const Employee& other) const {
        return name < other.name;
    }
    bool operator==(const Employee& other) const {
    return name == other.name;
    }
};

struct EmployeeHash {
    size_t operator()(const Employee& e) const {
        return std::hash<std::string>()(e.name);
    }
};

int main() {
    std::deque<Employee> employees;
    std::ifstream input("input.txt");
    std::string name, hire_date, position;
    double base_salary;

    while (getline(input, name)) {
        getline(input, hire_date);
        input >> position >> base_salary;
        input.ignore();
        employees.push_back(Employee(name, hire_date, position, base_salary));
    }
    input.close();

    std::ofstream output("output.txt");
    output << "Original container:\n";
    for (const auto& e : employees) {
        output << e << std::endl;
    }

    // Добавление объектов в контейнер set
    std::set<Employee> employees_set(employees.begin(), employees.end());

    output << "\nSet container:\n";
    for (const auto& e : employees_set) {
        output << e << std::endl;
    }

    // Добавление объектов в контейнер unordered_set
    std::unordered_set<Employee, EmployeeHash> employees_unordered_set(employees.begin(), employees.end());

    output << "\nUnordered set container:\n";
    for (const auto& e : employees_unordered_set) {
        output << e << std::endl;
    }

    output.close();

    return 0;
}
