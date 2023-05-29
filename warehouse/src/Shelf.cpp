#include <string>
#include "include/IContainer.hpp"

Shelf::Shelf(){

}

bool Shelf::swapPallet(int slot, int slot2){
    Pallet temp = this->pallets[slot];
    this->pallets[slot] = this->pallets[slot2];
    this->pallets[slot2] = temp;
    return true;
}

bool Shelf::isEmpty(){
    if(this->pallets[0].getItemCount() == 0 && this->pallets[1].getItemCount() == 0 && this->pallets[2].getItemCount() == 0 && this->pallets[3].getItemCount() == 0){
        return true;
    }   else {
        return false;
    }
}

bool Shelf::isFull(){
    if(this->pallets[0].getRemainingSpace() == 0 && this->pallets[1].getRemainingSpace() == 0 && this->pallets[2].getRemainingSpace() == 0 && this->pallets[3].getRemainingSpace() == 0){
        return true;
    }   else {
        return false;
    }
}