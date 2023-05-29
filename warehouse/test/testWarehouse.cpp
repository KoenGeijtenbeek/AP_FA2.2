#include "include/catch.hpp"

#include "../src/include/warehouse.hpp"
#include <iostream>

///////////////////////////////////////////////////////////////
//                                                           //
//                    Warehouse unittests                    //
//                                                           //
///////////////////////////////////////////////////////////////
//                                                           //
// This file contains all testcases for the Warehouse class. //
// Currently it only contains tests for the rearranging of   //
// shelves. All other Warehouse functions will also need to  //
// be tested. You will have to do this yourself.             //
//                                                           //
// For information on how to write testcases with catch2,    //
// see https://github.com/catchorg/Catch2.                   //
//                                                           //
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
//                Functions used in testcases                //
///////////////////////////////////////////////////////////////

/// \brief 
/// Creates a mock Warehouse.
/// \return Warehouse with shelf of books.
/// \details
/// Creates a Warehouse with 3 unsorted shelves with a total of 100 Books, 60 Boxes, and 60 Toy Bears.
/// \n Adds forklift certified employee Bob.
/// \n This function can be used in testcases to avoid the repeated construction of Warehouse objects.
Warehouse createMockWarehouse(){
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Books", 100, 40), 
        Pallet("Boxes", 100, 10), 
        Pallet("Books", 100, 20), 
        Pallet("Books", 100, 20)
    };

    Shelf shelf2 = Shelf();
    shelf2.pallets = {
        Pallet("Books", 100, 15), 
        Pallet("Boxes", 100, 20), 
        Pallet("Books", 100, 5), 
        Pallet("Boxes", 100, 30)
    };

    Shelf shelf3 = Shelf();
    shelf3.pallets = {
        Pallet("Toy Bears", 100, 20), 
        Pallet("Toy Bears", 100, 10), 
        Pallet(), 
        Pallet("Toy Bears", 100, 30)
    };
    
    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);
    warehouse.addShelf(shelf3);

    warehouse.addEmployee(Employee("Bob", true));

    return warehouse;
}


///////////////////////////////////////////////////////////////
//           Warehouse::rearrangeShelf test cases            //
///////////////////////////////////////////////////////////////

TEST_CASE("Rearrange empty shelf", "Warehouse::rearrangeShelf"){
    // Construct empty warehouse and add empty shelf and forklift certified Employee.
    Warehouse warehouse = Warehouse();
    warehouse.addShelf(Shelf());
    warehouse.addEmployee(Employee("Bob", true));

    // Check if shelf is already arranged.
    // Empty shelf should already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.rearrangeShelf(warehouse.shelves[0]);
    // Should be successful
    REQUIRE(successful);

    // Check if shelf is now correctly arranged.
    // Empty shelf should still be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);
}

TEST_CASE("Rearrange full shelf", "Warehouse::rearrangeShelf"){
    // Construct warehouse with unsorted shelf of books.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Books", 100, 20), 
        Pallet("Books", 100, 40), 
        Pallet("Books", 100, 30), 
        Pallet("Books", 100, 10)
    };

    warehouse.addEmployee(Employee("Bob", true));
    warehouse.addShelf(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.rearrangeShelf(warehouse.shelves[0]);
    // Should be successful
    REQUIRE(successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 10);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 40);
}

TEST_CASE("Rearrange half filled shelf", "Warehouse::rearrangeShelf"){
    // Construct empty warehouse and unsorted shelf of books.
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

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.rearrangeShelf(warehouse.shelves[0]);
    // Should be successful
    REQUIRE(successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 40);
}

TEST_CASE("Rearrange shelf without qualified employee", "Warehouse::rearrangeShelf"){
    // Construct warehouse with unsorted shelf of books.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Books", 100, 20), 
        Pallet("Books", 100, 40), 
        Pallet("Books", 100, 30), 
        Pallet("Books", 100, 10)
    };
    
    warehouse.addEmployee(Employee("Bert", false));
    warehouse.addShelf(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.rearrangeShelf(warehouse.shelves[0]);
    // Should fail
    REQUIRE(!successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now still not be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);
}

TEST_CASE("Rearrange shelf with quallified, but busy, employee", "Warehouse::rearrangeShelf"){
    // Construct warehouse with unsorted shelf of books.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Books", 100, 20), 
        Pallet("Books", 100, 40), 
        Pallet("Books", 100, 30), 
        Pallet("Books", 100, 10)
    };
    
    Employee bert = Employee("Bert", true);
    bert.setBusy(true);

    warehouse.addEmployee(bert);
    warehouse.addShelf(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.rearrangeShelf(warehouse.shelves[0]);
    // Should fail
    REQUIRE(!successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now still not be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);
}


//single shelf tests:


TEST_CASE("Pick items from 1 full shelf of same item", "Warehouse::pickItems"){
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 100)
    };

    warehouse.addShelf(shelf1);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 100);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 100);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 100);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 100);

    bool successful = warehouse.pickItems("Cheese", 258);
    REQUIRE(successful);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 42);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 100);
}

TEST_CASE("Picks items from 1 shelf with too few items", "Warehouse::pickItems"){
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Cheese", 100, 67),
        Pallet("Cheese", 100, 50),
        Pallet("Cheese", 100, 60),
        Pallet("Cheese", 100, 80)
    };

    warehouse.addShelf(shelf1);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 67);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 50);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 60);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 80);

    bool successful = warehouse.pickItems("Cheese", 258);
    REQUIRE(!successful);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 67);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 50);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 60);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 80);
}

TEST_CASE("Picks items from 1 shelf with exactly enough items", "Warehouse::pickItems"){
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Cheese", 100, 100),
        Pallet("Bananas", 100, 80),
        Pallet("Cheese", 100, 80),
        Pallet("Cheese", 100, 78)
    };

    warehouse.addShelf(shelf1);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 100);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 80);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 80);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 78);

    bool successful = warehouse.pickItems("Cheese", 258);
    REQUIRE(successful);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 80);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);
}

TEST_CASE("Pick items from 1 shelf of wrong items", "Warehouse::pickItems"){
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Bananas", 100, 99),
        Pallet("Mayonnaise", 100, 10),
        Pallet("Cheese", 100, 1),
        Pallet("Bacon", 100, 30)
    };

    warehouse.addShelf(shelf1);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 99);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 10);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 1);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 30);

    bool successful = warehouse.pickItems("Cheese", 258);
    REQUIRE(!successful);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 99);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 10);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 1);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 30);
}

TEST_CASE("Pick items from empty shelf", "Warehouse::pickItems"){
    Warehouse warehouse = Warehouse();
    warehouse.addShelf(Shelf());

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    bool successful = warehouse.pickItems("Cheese", 258);
    REQUIRE(!successful);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);
}

//multiple shelves tests:

TEST_CASE("Pick items from multiple full shelves of same item", "Warehouse::pickItems"){
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 100)
    };
    Shelf shelf2 = Shelf();
    shelf2.pallets = {
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 100)
    };
    Shelf shelf3 = Shelf();
    shelf3.pallets = {
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 100)
    };


    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);
    warehouse.addShelf(shelf3);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 100);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 100);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 100);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 100);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 100);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 100);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 100);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 100);

    REQUIRE(warehouse.shelves[2].pallets[0].getItemCount() == 100);
    REQUIRE(warehouse.shelves[2].pallets[1].getItemCount() == 100);
    REQUIRE(warehouse.shelves[2].pallets[2].getItemCount() == 100);
    REQUIRE(warehouse.shelves[2].pallets[3].getItemCount() == 100);

    bool successful = warehouse.pickItems("Cheese", 1041);
    REQUIRE(successful);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[2].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[2].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[2].pallets[2].getItemCount() == 59);
    REQUIRE(warehouse.shelves[2].pallets[3].getItemCount() == 100);
}

TEST_CASE("Pick items from multiple shelves with too few items", "Warehouse::pickItems"){
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Cheese", 100, 80),
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
        Pallet("Cheese", 100, 50),
        Pallet("Cheese", 100, 100),
        Pallet("Cheese", 100, 80)
    };


    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);
    warehouse.addShelf(shelf3);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 80);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 90);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 10);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 100);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 100);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 30);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 60);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 10);

    REQUIRE(warehouse.shelves[2].pallets[0].getItemCount() == 70);
    REQUIRE(warehouse.shelves[2].pallets[1].getItemCount() == 50);
    REQUIRE(warehouse.shelves[2].pallets[2].getItemCount() == 100);
    REQUIRE(warehouse.shelves[2].pallets[3].getItemCount() == 80);

    bool successful = warehouse.pickItems("Cheese", 781);
    REQUIRE(!successful);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 80);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 90);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 10);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 100);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 100);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 30);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 60);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 10);

    REQUIRE(warehouse.shelves[2].pallets[0].getItemCount() == 70);
    REQUIRE(warehouse.shelves[2].pallets[1].getItemCount() == 50);
    REQUIRE(warehouse.shelves[2].pallets[2].getItemCount() == 100);
    REQUIRE(warehouse.shelves[2].pallets[3].getItemCount() == 80);
}

TEST_CASE("Pick items from multiple shelves with exactly enough items", "Warehouse::pickItems"){
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
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


    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);
    warehouse.addShelf(shelf3);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 90);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 10);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 100);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 100);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 30);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 60);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 10);

    REQUIRE(warehouse.shelves[2].pallets[0].getItemCount() == 70);
    REQUIRE(warehouse.shelves[2].pallets[1].getItemCount() == 50);
    REQUIRE(warehouse.shelves[2].pallets[2].getItemCount() == 100);
    REQUIRE(warehouse.shelves[2].pallets[3].getItemCount() == 80);

    bool successful = warehouse.pickItems("Cheese", 650);
    REQUIRE(successful);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[2].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[2].pallets[1].getItemCount() == 50);
    REQUIRE(warehouse.shelves[2].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[2].pallets[3].getItemCount() == 0);
}

TEST_CASE("Pick items from multiple shelves with wrong items", "Warehouse::pickItems"){
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Bananas", 100, 80),
        Pallet("Cheese", 100, 90),
        Pallet("Bacon", 100, 10),
        Pallet("Lettuce", 100, 100)
    };
    Shelf shelf2 = Shelf();
    shelf2.pallets = {
        Pallet("Mustard", 100, 100),
        Pallet("Tomatoes", 100, 30),
        Pallet("Yoghurt", 100, 60),
        Pallet("Cheese", 100, 10)
    };
    Shelf shelf3 = Shelf();
    shelf3.pallets = {
        Pallet("Baguettes", 100, 70),
        Pallet("Cheese", 100, 50),
        Pallet("Pancake mix", 100, 100),
        Pallet("Cheese", 100, 80)
    };


    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);
    warehouse.addShelf(shelf3);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 80);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 90);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 10);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 100);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 100);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 30);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 60);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 10);

    REQUIRE(warehouse.shelves[2].pallets[0].getItemCount() == 70);
    REQUIRE(warehouse.shelves[2].pallets[1].getItemCount() == 50);
    REQUIRE(warehouse.shelves[2].pallets[2].getItemCount() == 100);
    REQUIRE(warehouse.shelves[2].pallets[3].getItemCount() == 80);

    bool successful = warehouse.pickItems("Cheese", 500);
    REQUIRE(!successful);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 80);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 90);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 10);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 100);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 100);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 30);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 60);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 10);

    REQUIRE(warehouse.shelves[2].pallets[0].getItemCount() == 70);
    REQUIRE(warehouse.shelves[2].pallets[1].getItemCount() == 50);
    REQUIRE(warehouse.shelves[2].pallets[2].getItemCount() == 100);
    REQUIRE(warehouse.shelves[2].pallets[3].getItemCount() == 80);
}

TEST_CASE("Pick items from multiple empty shelves", "Warehouse::pickItems"){
    Warehouse warehouse = Warehouse();
    


    warehouse.addShelf(Shelf());
    warehouse.addShelf(Shelf());
    warehouse.addShelf(Shelf());

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[2].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[2].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[2].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[2].pallets[3].getItemCount() == 0);

    bool successful = warehouse.pickItems("Cheese", 500);
    REQUIRE(!successful);

    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[2].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[2].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[2].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[2].pallets[3].getItemCount() == 0);
}