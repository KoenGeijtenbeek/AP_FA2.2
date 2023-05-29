#include <string>
#include "include/Employee.hpp"

Employee::Employee(std::string name, bool forkliftCertificate){
    this->name = name;
    this->busy = busy;
    this->forkliftCertificate = forkliftCertificate;
}

std::string Employee::getName(){
    return this->name;
}

bool Employee::getBusy(){
    return this->busy;
}

void Employee::setBusy(bool busy){
    this->busy = busy;
}

bool Employee::getForkliftCertificate(){
    return this->forkliftCertificate;
}

void Employee::setForkliftCertificate(bool forkliftCertificate){
    this->forkliftCertificate = forkliftCertificate;
}