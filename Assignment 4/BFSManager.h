#ifndef BFSMANAGER_H
#define BFSMANAGER_H

class BFSManager {
public:
    BFSManager();
    ~BFSManager();
    void saveInitialState(int** cityMap, int totalRows, int totalCols);
    void enqueueCoordinate(int**& cityMap, int row, int col);
    void processOneLevel(int**& cityMap, int maxRows, int maxCols);
    void propagateInfection(int**& cityMap, int currentR, int currentC, int maxRows, int maxCols);
    void revertToInitial(int**& cityMap, int rows, int cols);
    bool queueIsEmpty() const;
    bool inQueueAlready(int row, int col) const;

private:
    struct Node {
        int r;
        int c;
        Node* next;
        Node(int row, int col) : r(row), c(col), next(nullptr) {}
    };

    Node* queueFront;
    int** originalMap;
    int numRows, numCols;
    void addSentinel();
};

#endif
