#include <string>
#include "include/IContainer.hpp"

Pallet::Pallet(std::string itemName, int itemCapacity, int itemCount){
    this->itemName = itemName;
    this->itemCapacity = itemCapacity;
    this->itemCount = itemCount;
}

Pallet::Pallet(){

}

std::string Pallet::getItemName(){
    return this->itemName;
}

int Pallet::getItemCount(){
    return this->itemCount;
}

int Pallet::getRemainingSpace(){
    return this->itemCapacity - this->itemCount;
}

bool Pallet::reallocateEmptyPallet(std::string itemName, int itemCapacity){
    //TODO: ???
}

bool takeOne(){
    //TODO: pak 1 item?
}

bool putOne(){
    //TODO: put 1 item?
}