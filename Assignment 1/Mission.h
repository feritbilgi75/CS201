#ifndef MISSION_H
#define MISSION_H
#include <string>

using namespace std;


/*
Ferit Bilgi
Section 3
22102554
*/

class Mission {
public:
    Mission(const string& name, const string& launchDate, const string& destination);
    Mission();
    ~Mission();

    string getName() const;
    string getLaunchDate() const;
    string getDestination() const;
    int getSpacecraftCount() const;
    void addSpacecraft(const string& spacecraftName);
    void removeSpacecraft(const string& spacecraftName);
    void showDetails() const;
    string* getAssignedSpacecrafts();
    

private:
    string name;
    string launchDate;
    string destination;
    string* assignedSpacecrafts;
    int spacecraftCount;
};

#endif
