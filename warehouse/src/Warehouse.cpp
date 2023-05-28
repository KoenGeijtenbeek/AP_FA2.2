#include <string>
#include <vector>
#include "include/IContainer.hpp"
#include "include/Employee.hpp"
#include "include/Warehouse.hpp"

Warehouse::Warehouse(){
    
}

void Warehouse::addEmployee(Employee employee){
    this->Employees.push_back(employee);
}

void Warehouse::addShelf(Shelf shelf){
    this->Shelves.push_back(shelf);
}

bool Warehouse::rearrangeShelf(Shelf& shelf){
    //TODO: sorteer pallets op een shelf op volgorde van itemCount oplopend
}

bool Warehouse::pickItems(std::string itemName, int itemCount){
    //TODO: pakt items uit pallets. slaagt als genoeg items van de itemname aanwezig zijn, verdeeld over alle pallets. gebruik hierbij takeOne()
}