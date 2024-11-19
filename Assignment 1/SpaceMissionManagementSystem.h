#ifndef SPACEMISSIONMANAGEMENTSYSTEM_H
#define SPACEMISSIONMANAGEMENTSYSTEM_H

#include "Mission.h"
#include "Spacecraft.h"
#include <string>


using namespace std;

/*
Ferit Bilgi
Section 3
22102554
*/


class SpaceMissionManagementSystem {
public:
    SpaceMissionManagementSystem();
    ~SpaceMissionManagementSystem();

    void addMission(const string name, const string launchDate, const string destination);
    void removeMission(const string name);
    void addSpacecraft(const string name, const string type);
    void removeSpacecraft(const string name);
    void assignSpacecraftToMission(const string spacecraftName, const string missionName);
    void dropSpacecraftFromMission(const string spacecraftName);
    void dropSpacecraftFromMiss(const string spacecraftName);
    void showAllMissions() const;
    void showAllSpacecrafts() const;
    void showMission(const string name) const;
    void showSpacecraft(const string name) const;
    

private:
    Mission* missions;
    Spacecraft* spacecrafts;
    int missionCount;
    int spacecraftCount;

    Mission* findMission(const string& name) const;
    
    Spacecraft *findSpacecraft(const string &name) const;
    void expandMissions();
    void expandSpacecrafts();
};

#endif
