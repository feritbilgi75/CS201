
#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <string>

/*
Ferit Bilgi
Section 3
22102554
*/
using namespace std;

class Spacecraft {
public:
    Spacecraft(const string& name, const string& type);
    Spacecraft();
    string getName() const;
    string getType() const;
    string getStatus() const;
    void setStatus(const string& status);
    void showDetails() const;

private:
    string name;
    string type;
    string status;
};

#endif
