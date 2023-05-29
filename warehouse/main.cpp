#include <iostream>
#include "src/include/IContainer.hpp"
#include "src/include/Warehouse.hpp"
#include "src/include/Employee.hpp"


int main(void){
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Books", 100, 40), 
        Pallet("Books", 100, 20), 
        Pallet(), 
        Pallet()
    };
    
    warehouse.addEmployee(Employee("Bob", true));
    warehouse.addShelf(shelf1);
    std::cout << std::endl << "rearrangeShelf():" << std::endl << std::endl;
    for(std::array<Pallet, 4>::iterator it = shelf1.pallets.begin(); it != shelf1.pallets.end(); ++it){
        std::cout << *it;
    }

    bool successful = warehouse.rearrangeShelf(shelf1);
    if(successful){
        std::cout << std::endl << "Rearrangement successful." << std::endl << std::endl;
    } else {
        std::cout << std::endl << "Rearrangement failed." << std::endl << std::endl;
    }

    for(std::array<Pallet, 4>::iterator it = shelf1.pallets.begin(); it != shelf1.pallets.end(); ++it){
        std::cout << *it;
    }






    
    shelf1.pallets = {
        Pallet("Cheese", 100, 0),
        Pallet("Cheese", 100, 90),
        Pallet("Cheese", 100, 10),
        Pallet("Cheese", 100, 100)
    };
    Shelf shelf2 = Shelf();
    shelf2.pallets = {
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 30),
        Pallet("Cheese", 100, 60),
        Pallet("Cheese", 100, 10)
    };
    Shelf shelf3 = Shelf();
    shelf3.pallets = {
        Pallet("Cheese", 100, 70),
        Pallet("Apples", 100, 50),
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 80)
    };
    warehouse.shelves[0] = shelf1;
    warehouse.addShelf(shelf2);
    warehouse.addShelf(shelf3);
    std::cout << std::endl << "pickItems(): " << std::endl << std::endl;
    for(std::vector<Shelf>::iterator it = warehouse.shelves.begin(); it != warehouse.shelves.end(); ++it){
        for(int i = 0; i < 4; i++){
            std::cout << it->pallets[i];
        }
        std::cout << std::endl;
    }

    successful = warehouse.pickItems("Cheese", 650);

    if(successful){
        std::cout << std::endl << "Item pick-up successful." << std::endl << std::endl;
    } else {
        std::cout << std::endl << "Item pick-up failed." << std::endl << std::endl;
    }

    for(std::vector<Shelf>::iterator it = warehouse.shelves.begin(); it != warehouse.shelves.end(); ++it){
        for(int i = 0; i < 4; i++){
            std::cout << it->pallets[i];
        }
        std::cout << std::endl;
    }

}

