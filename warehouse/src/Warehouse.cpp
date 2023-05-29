#include <string>
#include <vector>
#include <algorithm>
#include "include/IContainer.hpp"
#include "include/Employee.hpp"
#include "include/Warehouse.hpp"


Warehouse::Warehouse(){
    
}

void Warehouse::addEmployee(Employee employee){
    this->employees.push_back(employee);
}

void Warehouse::addShelf(Shelf shelf){
    this->shelves.push_back(shelf);
}


bool Warehouse::rearrangeShelf(Shelf& shelf){
    for(std::vector<Employee>::iterator it = this->employees.begin(); it != this->employees.end(); ++it){
        if(!it->getBusy() && it->getForkliftCertificate()){
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    if(shelf.pallets[i] > shelf.pallets[j]){
                        shelf.swapPallet(i, j);
                    }
                }
            }
            return true;
        } else {
            continue;
        }
    } 
    return false;
}

bool Warehouse::pickItems(std::string itemName, int itemCount){
    //check of er genoeg items in heel het warehouse zijn
    int counter = 0;
    for(std::vector<Shelf>::iterator it = shelves.begin(); it != shelves.end(); ++it){
        for(int i = 0; i < 4; i++){
            if(it->pallets[i].getItemName() == itemName){
                counter += it->pallets[i].getItemCount();
            }
        }
    }
    if(counter < itemCount){
        return false;
    } else {
        counter = 0;
        for(std::vector<Shelf>::iterator it = shelves.begin(); it != shelves.end(); ++it){
            for(int i = 0; i < 4; i++){
                if(it->pallets[i].getItemName() == itemName){
                    while(it->pallets[i].takeOne() && counter + 1 != itemCount){ //blijft van elke pallet van elke shelf items pakken tot de benodigde itemCount is bereikt
                        counter++;
                    }
                    if(counter + 1 == itemCount){
                        return true;
                    }
                }
            }
        }
    }
}