#include "SpaceMissionManagementSystem.h"
#include <iostream>
using namespace std;

/*
Ferit Bilgi
Section 3
22102554
*/


SpaceMissionManagementSystem::SpaceMissionManagementSystem(){
    this->missionCount = 0;
    this->spacecraftCount = 0;
    this->missions = nullptr;
    this->spacecrafts = nullptr;
} 

SpaceMissionManagementSystem::~SpaceMissionManagementSystem() {
    delete[] missions;
    delete[] spacecrafts;
}

Mission* SpaceMissionManagementSystem::findMission(const string& name) const {
    for (int i = 0; i < missionCount; i++) {
        if (missions[i].getName() == name) return &missions[i];
    }
    return nullptr;
}

Spacecraft* SpaceMissionManagementSystem::findSpacecraft(const string& name) const {
    for (int i = 0; i < spacecraftCount; i++) {
        if (spacecrafts[i].getName() == name) return &spacecrafts[i];
    }
    return nullptr;
}

void SpaceMissionManagementSystem::expandMissions() {
    Mission* newMissions = new Mission[missionCount + 1];
    for (int i = 0; i < missionCount; i++) newMissions[i] = missions[i];
    delete[] missions;
    missions = newMissions;
}

void SpaceMissionManagementSystem::expandSpacecrafts() {
    Spacecraft* newSpacecrafts = new Spacecraft[spacecraftCount + 1];
    for (int i = 0; i < spacecraftCount; i++) newSpacecrafts[i] = spacecrafts[i];
    delete[] spacecrafts;
    spacecrafts = newSpacecrafts;
}

void SpaceMissionManagementSystem::addMission(const string name, const string launchDate, const string destination) {
    if (findMission(name)) {
        cout << "Cannot add mission. Mission " << name << " already exists." << endl;
        return;
    }
    expandMissions();
    missions[missionCount] = Mission(name, launchDate, destination);
    missionCount++;
    cout << "Added mission " << name << "." << endl;
}

void SpaceMissionManagementSystem::dropSpacecraftFromMiss(const string spacecraftName) {
    Spacecraft* spacecraft = findSpacecraft(spacecraftName);
    if (spacecraft == nullptr) {
        cout << "Cannot drop spacecraft. Spacecraft "<< spacecraftName << " does not exist." << endl;
        return;
    }
    if (spacecraft->getStatus() != "Assigned"){
        cout << "Cannot drop spacecraft. Spacecraft " << spacecraftName << " is not assigned to any mission." << endl;
        return;
    }

    int indexOfMission = -1;
    
    for (int i = 0; i < missionCount; i++) {
        Mission* mission = &(missions[i]);
        for (int j = 0; j < mission->getSpacecraftCount(); j++) {
            if (mission->getAssignedSpacecrafts()[j] == spacecraftName) {
                indexOfMission = i;
                break;
            }
        }
        if (indexOfMission != -1) break;
    }

    if (indexOfMission == -1) {
        cout << "Cannot drop spacecraft. Spacecraft " << spacecraftName << " is not assigned to any mission." << endl;
        return;
    }
    spacecraft->setStatus("Available");
    Mission* mission = &(missions[indexOfMission]);
    mission->removeSpacecraft(spacecraftName);
    
    
}

void SpaceMissionManagementSystem::removeMission(const string name) {
    Mission* mission = findMission(name);
    if (mission == nullptr) {
        cout << "Cannot remove mission. Mission " << name << " does not exist." << endl;
        return;
    }
    int spaceCraftCount2 = mission->getSpacecraftCount();
    if(spaceCraftCount2 > 0){
        for(int i = 0; i < spaceCraftCount2; i++){
            const string nameOfCraft = mission->getAssignedSpacecrafts()[0];
            dropSpacecraftFromMiss(nameOfCraft);
            
        }
        
    }

    missionCount--;    
    Mission* newMissions = new Mission[missionCount];
    int newMissionCount = 0;
    for (int i = 0; i < missionCount + 1; i++) {
        if(!(missions[i].getName() == name)){
            newMissions[newMissionCount] = missions[i];
            newMissionCount++;
        }
    }
    delete[] missions;
    missions = newMissions;


    cout << "Removed mission " << name << "." << endl;
}

void SpaceMissionManagementSystem::addSpacecraft(const string name, const string type) {
    if (findSpacecraft(name)) {
        cout << "Cannot add spacecraft. Spacecraft " << name << " already exists." << endl;
        return;
    }
    expandSpacecrafts();
    spacecrafts[spacecraftCount] = Spacecraft(name, type);
    spacecraftCount++;
    cout << "Added spacecraft " << name << "." << endl;
}

void SpaceMissionManagementSystem::removeSpacecraft(const string name) {
    Spacecraft* spacecraft = findSpacecraft(name);
    if (!spacecraft) {
        cout << "Cannot remove spacecraft. Spacecraft " << name << " does not exist." << endl;
        return;
    }
    if (spacecraft->getStatus() == "Assigned") {
        cout << "Cannot remove spacecraft. Spacecraft " << name << " is assigned to a mission." << endl;
        return;
    }

    spacecraftCount--;

    Spacecraft* newCrafts = new Spacecraft[spacecraftCount];
    int newSpacecraftCount = 0;
    for (int i = 0; i < spacecraftCount + 1; i++) {
        if(!(spacecrafts[i].getName() == name)){
            newCrafts[newSpacecraftCount] = spacecrafts[i];
            newSpacecraftCount++;
        }
    }
    delete[] spacecrafts;
    spacecrafts = newCrafts;
    

    
    cout << "Removed spacecraft " << name << "." << endl;
}

void SpaceMissionManagementSystem::assignSpacecraftToMission(const string spacecraftName, const string missionName) {
    Spacecraft* spacecraft = findSpacecraft(spacecraftName);
    Mission* mission = findMission(missionName);
    if(!spacecraft){
       cout << "Cannot assign spacecraft. Spacecraft "<< spacecraftName <<" does not exist."<< endl;
        return; 
    }
    if(!mission){
       cout << "Cannot assign spacecraft. Mission "<< missionName <<" does not exist."<< endl;
        return; 
    }
    
    if (spacecraft->getStatus() == "Assigned") {
        int indexOfMission = -1;
    
        for (int i = 0; i < missionCount; i++) {
            Mission* mission = &(missions[i]);
            for (int j = 0; j < mission->getSpacecraftCount(); j++) {
                if (mission->getAssignedSpacecrafts()[j] == spacecraftName) {
                    indexOfMission = i;
                    break;
                }
                
        }
        if (indexOfMission != -1){
                break;
            }
        
    }
    cout << "Cannot assign spacecraft. Spacecraft " << spacecraftName << " is already assigned to mission "<< missions[indexOfMission].getName() << "."<< endl;
        return;
    }
    spacecraft->setStatus("Assigned");
    mission->addSpacecraft(spacecraftName);
    cout << "Assigned spacecraft " << spacecraftName << " to mission " << missionName << "." << endl;
}




void SpaceMissionManagementSystem::dropSpacecraftFromMission(const string spacecraftName) {
    Spacecraft* spacecraft = findSpacecraft(spacecraftName);
    if (spacecraft == nullptr) {
        cout << "Cannot drop spacecraft. Spacecraft "<< spacecraftName << " does not exist." << endl;
        return;
    }
    if (spacecraft->getStatus() != "Assigned"){
        cout << "Cannot drop spacecraft. Spacecraft " << spacecraftName << " is not assigned to any mission." << endl;
        return;
    }

    int indexOfMission = -1;
    
    for (int i = 0; i < missionCount; i++) {
        Mission* mission = &(missions[i]);
        for (int j = 0; j < mission->getSpacecraftCount(); j++) {
            if (mission->getAssignedSpacecrafts()[j] == spacecraftName) {
                indexOfMission = i;
                break;
            }
        }
        if (indexOfMission != -1) break;
    }

    if (indexOfMission == -1) {
        cout << "Cannot drop spacecraft. Spacecraft " << spacecraftName << " is not assigned to any mission." << endl;
        return;
    }
    spacecraft->setStatus("Available");
    Mission* mission = &(missions[indexOfMission]);
    mission->removeSpacecraft(spacecraftName);
    cout << "Dropped spacecraft " << spacecraftName << " from mission " << mission->getName() << "." << endl;
    
    
}





void SpaceMissionManagementSystem::showAllMissions() const {
    cout << "Missions in the space mission management system:" << endl;
    if (missionCount == 0) {
        cout << "None" << endl;
        return;
    }
    for (int i = 0; i < missionCount; i++) {
        cout << "Mission: " << missions[i].getName() << ", Launch Date: " << missions[i].getLaunchDate()
             << ", Destination: " << missions[i].getDestination() << ", Assigned Spacecraft Count: " << missions[i].getSpacecraftCount() << endl;
    }
}

void SpaceMissionManagementSystem::showAllSpacecrafts() const {
    cout << "Spacecrafts in the space mission management system:" << endl;
    if (spacecraftCount == 0) {
        cout << "None" << endl;
        return;
    }
    for (int i = 0; i < spacecraftCount; i++) {
        cout << "Spacecraft: " << spacecrafts[i].getName() << ", Type: " << spacecrafts[i].getType()
             << ", Status: " << spacecrafts[i].getStatus() << endl;
    }
}

void SpaceMissionManagementSystem::showMission(const string name) const {
    Mission* mission = findMission(name);
    if (!mission) {
        cout << "Cannot show mission. Mission " << name << " does not exist." << endl;
        return;
    }
    mission->showDetails();
}

void SpaceMissionManagementSystem::showSpacecraft(const string name) const {
    Spacecraft* spacecraft = findSpacecraft(name);
    if (!spacecraft) {
        cout << "Cannot show spacecraft. Spacecraft " << name << " does not exist." << endl;
        return;
    }
    spacecraft->showDetails();
}
