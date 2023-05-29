#pragma once
#include <string>
#include <ostream>
#include <vector>
#include "Employee.hpp"
#include "IContainer.hpp"


class Warehouse {
    public:
        std::vector<Employee> employees;
        std::vector<Shelf> shelves;
        Warehouse();
        void addEmployee(Employee employee);
        void addShelf(Shelf shelf);
        bool rearrangeShelf(Shelf& shelf);
        bool pickItems(std::string itemName, int itemCount);
};