#pragma once
#include <string> 
#include <ostream>
#include <array>


class IContainer {
    public:
        virtual bool isEmpty() = 0;
        virtual bool isFull() = 0;
};

class Pallet : IContainer {
    private:
        int itemCount;
        std::string itemName;
        int itemCapacity;
    public:
        Pallet(std::string itemName, int itemCapacity, int itemCount);
        Pallet();
        std::string getItemName();
        int getItemCount();
        int getRemainingSpace();
        bool reallocateEmptyPallet(std::string itemName, int itemCapacity);
        bool takeOne();
        bool putOne();
        bool isEmpty();
        bool isFull();
};

class Shelf : IContainer {
    public:
        std::array<Pallet, 4> pallets;
        Shelf();
        bool swapPallet(int slot, int slot2);
        bool isEmpty();
        bool isFull();
};