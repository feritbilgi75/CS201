/*
Ferit Bilgi
Section 3
22102554
*/



#include "Mission.h"
#include <iostream>
using namespace std;

Mission::Mission(){
    
}

Mission::Mission(const string& name, const string& launchDate, const string& destination){
    this->name = name;
    this->launchDate = launchDate;
    this->destination = destination;
    this->spacecraftCount = 0;
    this->assignedSpacecrafts = nullptr;
}
    

Mission::~Mission() {
    delete[] assignedSpacecrafts;
}

string Mission::getName() const {
    return name;
}

string Mission::getLaunchDate() const {
    return launchDate;
}

string Mission::getDestination() const {
    return destination;
}

int Mission::getSpacecraftCount() const {
    return spacecraftCount;
}



void Mission::addSpacecraft(const string& spacecraftName) {
    string* newAssignedSpacecrafts = new string[spacecraftCount + 1];
    for (int i = 0; i < spacecraftCount; i++) {
        newAssignedSpacecrafts[i] = assignedSpacecrafts[i];
    }
    newAssignedSpacecrafts[spacecraftCount] = spacecraftName;
    delete[] assignedSpacecrafts;
    assignedSpacecrafts = newAssignedSpacecrafts;
    spacecraftCount++;
}


void Mission::removeSpacecraft(const string& spacecraftName) {
    int indexToRemove = -1;
    
   
    for (int i = 0; i < spacecraftCount; i++) {
        if (assignedSpacecrafts[i] == spacecraftName) {
            indexToRemove = i;
            break;
        }
    }

    
    if (indexToRemove == -1) {
        cout << "Spacecraft " << spacecraftName << " not found in assigned spacecrafts." << endl;
        return;
    }


    if (spacecraftCount > 1) {
        string* newAssignedSpacecrafts = new string[spacecraftCount - 1];
        int newIndex = 0;

        // Copy all elements except the one to remove
        for (int i = 0; i < spacecraftCount; i++) {
            if (i != indexToRemove) {
                newAssignedSpacecrafts[newIndex] = assignedSpacecrafts[i];
                newIndex++;
            }
        }

        delete[] assignedSpacecrafts;
        assignedSpacecrafts = newAssignedSpacecrafts;
    } else {
        delete[] assignedSpacecrafts;
        assignedSpacecrafts = nullptr;
    }

    spacecraftCount--;
    
   
}





string* Mission::getAssignedSpacecrafts(){
    return assignedSpacecrafts;
}

void Mission::showDetails() const {
    cout << "Mission:\n "<<" Name: " << name << "\n  Launch Date: " << launchDate << "\n  Destination: " << destination
         << "\n  Assigned Spacecrafts:" << endl;
    if (spacecraftCount == 0) {
        cout << "    None" << endl;
    } else {
        for (int i = 0; i < spacecraftCount; i++) {
            cout << "  - " << assignedSpacecrafts[i] << endl;
        }
    }
}

