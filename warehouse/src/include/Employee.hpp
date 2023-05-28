#pragma once
#include <string>
#include <ostream>

class Employee {
    private:
        std::string name;
        bool busy;
        bool forkliftCertificate;

    public:
        Employee(std::string name, bool busy, bool forkliftCertificate);
        std::string getName();
        bool getBusy();
        void setBusy(bool busy);
        bool getForkliftCertificate();
        void setForkliftCertificate(bool forkliftCertificate);
};