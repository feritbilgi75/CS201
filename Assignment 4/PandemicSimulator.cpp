#include "PandemicSimulator.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

PandemicSimulator::PandemicSimulator(const std::string cityGridFile) {
    ifstream inFile(cityGridFile.c_str());
    if (!inFile) {
        cerr << "Error: cannot open file " << cityGridFile << endl;
        exit(1);
    }

    inFile >> rows >> cols;
    cityMap = new int*[rows];
    for (int i = 0; i < rows; i++) {
        cityMap[i] = new int[cols];
    }

    bfsTool = new BFSManager();

    for (int i = 0; i < rows; i++) {
        string line;
        inFile >> line;
        for (int j = 0; j < cols; j++) {
            cityMap[i][j] = line[j] - '0';
        }
    }
    inFile.close();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (cityMap[i][j] == 2) {
                if (!bfsTool->inQueueAlready(i, j)) {
                    bfsTool->enqueueCoordinate(cityMap, i, j);
                }
            }
        }
    }

    bfsTool->saveInitialState(cityMap, rows, cols);
}

PandemicSimulator::~PandemicSimulator() {
    delete bfsTool;
    for (int i = 0; i < rows; i++) {
        delete[] cityMap[i];
    }
    delete[] cityMap;
}

void PandemicSimulator::displayCityState(int day) {
    if (day == 0) {
        cout << "City state at day 0:" << endl;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                cout << cityMap[r][c];
            }
            cout << endl;
        }
    } else {
        for (int i = 0; i < day; i++) {
            bfsTool->processOneLevel(cityMap, rows, cols);
        }
        cout << "City state at day " << day << ":" << endl;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                cout << cityMap[r][c];
            }
            cout << endl;
        }
    }
    bfsTool->revertToInitial(cityMap, rows, cols);
}

void PandemicSimulator::simulateBlock(int row, int col) {
    int dayCount = 0;
    while (cityMap[row][col] != 2) {
        if (bfsTool->queueIsEmpty()) {
            dayCount = -1;
            break;
        }
        bfsTool->processOneLevel(cityMap, rows, cols);
        dayCount++;
    }
    cout << "Time for block (" << row << ", " << col << ") to be infected: " 
         << dayCount << " days." << endl;
    bfsTool->revertToInitial(cityMap, rows, cols);
}

void PandemicSimulator::simulatePandemic() {
    int stepsTaken = -1;
    while (!bfsTool->queueIsEmpty()) {
        bfsTool->processOneLevel(cityMap, rows, cols);
        stepsTaken++;
    }
    bool unreachable = false;
    for (int i = 0; i < rows && !unreachable; i++) {
        for (int j = 0; j < cols; j++) {
            if (cityMap[i][j] == 1) {
                unreachable = true;
                break;
            }
        }
    }
    if (!unreachable) {
        cout << "Minimum time for pandemic to spread to all blocks: " 
             << stepsTaken << " days." << endl;
    } else {
        cout << "Pandemic cannot spread to all blocks." << endl;
    }
    bfsTool->revertToInitial(cityMap, rows, cols);
}
