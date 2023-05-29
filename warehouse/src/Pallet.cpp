#include <string>
#include "include/IContainer.hpp"

Pallet::Pallet(std::string itemName, int itemCapacity, int itemCount){
    this->itemName = itemName;
    this->itemCapacity = itemCapacity;
    this->itemCount = itemCount;
}

Pallet::Pallet(){
    this->itemCount = 0;
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
    if(this->isEmpty()){
        this->itemName = itemName;
        this->itemCapacity = itemCapacity;
        return true;
    } else {
        return false;
    }
}

bool Pallet::isEmpty(){
    if(this->itemCount == 0){
        return true;
    } else {
        return false;
    }
}

bool Pallet::isFull(){
    if(this->getRemainingSpace() == 0){
        return true;
    } else {
        return false;
    }
}

bool Pallet::takeOne(){
    if(!this->isEmpty()){
        this->itemCount -= 1;
        return true;
    } else {
        return false;
    }
}

bool Pallet::putOne(){
    if(!this->isFull()){
        this->itemCount += 1;
        return true;
    } else {
        return false;
    }
}

bool Pallet::operator>(const Pallet &rhs) const{
    if (this->itemCount > rhs.itemCount){
        return false;
    } else {
        return true;
    }
}

std::ostream& operator<<(std::ostream&os, Pallet rhs){
    if(rhs.getItemCount() == 0){
        os << "Pallet contains nothing." << std::endl;
    } else {
        os << "Pallet contains " << rhs.getItemCount() << " " << rhs.getItemName() << "." << std::endl;
    }
    return os;
}