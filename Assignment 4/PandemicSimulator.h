#ifndef PANDEMICSIMULATOR_H
#define PANDEMICSIMULATOR_H

#include <string>
#include "BFSManager.h"

class PandemicSimulator {
public:
    PandemicSimulator(const std::string cityGridFile);
    ~PandemicSimulator();
    void displayCityState(int day);
    void simulateBlock(int row, int col);
    void simulatePandemic();

private:
    int** cityMap;      
    int rows, cols;     
    BFSManager* bfsTool; 
};

#endif
