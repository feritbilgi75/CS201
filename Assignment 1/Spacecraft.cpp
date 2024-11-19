#include "Spacecraft.h"
#include <iostream>
using namespace std;

/*
Ferit Bilgi
Section 3
22102554
*/

Spacecraft::Spacecraft(){

}
Spacecraft::Spacecraft(const string& name, const string& type) {
        this->name = name;
        this->type = type;
        this->status = "Available";
    }

string Spacecraft::getName() const {
    return name;
}

string Spacecraft::getType() const {
    return type;
}

string Spacecraft::getStatus() const {
    return status;
}

void Spacecraft::setStatus(const string& status) {
    this->status = status;
}

void Spacecraft::showDetails() const {
    cout << "Spacecraft: " << name << ", Type: " << type << ", Status: " << status << endl;
}
