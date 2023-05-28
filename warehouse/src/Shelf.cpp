#include <string>
#include "include/IContainer.hpp"

Shelf::Shelf(){

}

bool Shelf::swapPallet(int slot, int slot2){
    std::swap(this->pallets[slot], this->pallets[slot2]);
    return true;
    //TODO: something?
}

bool Shelf::isEmpty(){
    //TODO: als een shelf leeg is, zijn er 4 pallets met itemCount 0
}

bool Shelf::isFull(){
    //TODO: true wanneer alle 4 pallets vol zijn
}