#include "BFSManager.h"
#include <cstddef>

BFSManager::BFSManager() {
    queueFront = nullptr;
    originalMap = nullptr;
    numRows = 0;
    numCols = 0;
}

BFSManager::~BFSManager() {
    while (queueFront != nullptr) {
        Node* tmp = queueFront;
        queueFront = queueFront->next;
        delete tmp;
    }
    if (originalMap != nullptr) {
        for (int i = 0; i < numRows; i++) {
            delete[] originalMap[i];
        }
        delete[] originalMap;
    }
}

void BFSManager::saveInitialState(int** cityMap, int totalRows, int totalCols) {
    if (originalMap != nullptr) {
        for (int i = 0; i < numRows; i++) {
            delete[] originalMap[i];
        }
        delete[] originalMap;
        originalMap = nullptr;
    }

    numRows = totalRows;
    numCols = totalCols;

    originalMap = new int*[numRows];
    for (int i = 0; i < numRows; i++) {
        originalMap[i] = new int[numCols];
        for (int j = 0; j < numCols; j++) {
            originalMap[i][j] = cityMap[i][j];
        }
    }
}

void BFSManager::enqueueCoordinate(int**& cityMap, int row, int col) {
    if (!queueFront) {
        queueFront = new Node(row, col);
    } else {
        Node* curr = queueFront;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = new Node(row, col);
    }
    cityMap[row][col] = 2;
}

void BFSManager::addSentinel() {
    Node* sentinel = new Node(-1, -1);
    if (!queueFront) {
        queueFront = sentinel;
    } else {
        Node* trav = queueFront;
        while (trav->next) {
            trav = trav->next;
        }
        trav->next = sentinel;
    }
}

void BFSManager::processOneLevel(int**& cityMap, int maxRows, int maxCols) {
    addSentinel();
    while (queueFront) {
        if (queueFront->r == -1 && queueFront->c == -1) {
            Node* s = queueFront;
            queueFront = queueFront->next;
            delete s;
            break;
        }
        propagateInfection(cityMap, queueFront->r, queueFront->c, maxRows, maxCols);
        Node* popped = queueFront;
        queueFront = queueFront->next;
        delete popped;
    }
}

void BFSManager::propagateInfection(int**& cityMap, int currentR, int currentC, int maxRows, int maxCols) {
    if (currentR > 0) {
        if (cityMap[currentR - 1][currentC] == 1 && !inQueueAlready(currentR - 1, currentC)) {
            enqueueCoordinate(cityMap, currentR - 1, currentC);
        }
    }

    if (currentR < maxRows - 1) {
        if (cityMap[currentR + 1][currentC] == 1 && !inQueueAlready(currentR + 1, currentC)) {
            enqueueCoordinate(cityMap, currentR + 1, currentC);
        }
    }

    if (currentC > 0) {
        if (cityMap[currentR][currentC - 1] == 1 && !inQueueAlready(currentR, currentC - 1)) {
            enqueueCoordinate(cityMap, currentR, currentC - 1);
        }
    }

    if (currentC < maxCols - 1) {
        if (cityMap[currentR][currentC + 1] == 1 && !inQueueAlready(currentR, currentC + 1)) {
            enqueueCoordinate(cityMap, currentR, currentC + 1);
        }
    }
}

bool BFSManager::queueIsEmpty() const {
    return (queueFront == nullptr);
}

bool BFSManager::inQueueAlready(int row, int col) const {
    Node* temp = queueFront;
    while (temp) {
        if (temp->r == row && temp->c == col) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void BFSManager::revertToInitial(int**& cityMap, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cityMap[i][j] = originalMap[i][j];
        }
    }
    while (queueFront) {
        Node* tmp = queueFront;
        queueFront = queueFront->next;
        delete tmp;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (cityMap[i][j] == 2) {
                enqueueCoordinate(cityMap, i, j);
            }
        }
    }
}
