#include <iostream>
#include <ctime>
#include <cmath>


using namespace std;


//Linear Search
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
        return -1;
}


    //Linear Search Recursive
/*
int linearSearchRecursive(int arr[], int n, int key, int index = 0){
        if (index >= n) {
            return -1;
        }
        if (arr[index] == key) {
            return index;
        }
        return linearSearchRecursive(arr, n, key, index + 1);
    }
*/

int linearSearchRecursiveHelper(int arr[], int n, int key, int index) {
    if (index >= n) return -1;
    if (arr[index] == key) return index;
    return linearSearchRecursiveHelper(arr, n, key, index + 1);
}

// Wrapper for recursive search
int linearSearchRecursive(int arr[], int n, int key) {
    return linearSearchRecursiveHelper(arr, n, key, 0);
}

    //Binary Search
int binarySearch(int arr[], int size, int key) {
        int low = 0;
        int high = size - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] == key) return mid;
            else if (arr[mid] < key) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        return -1;
    }


//Jump Search
int jumpSearch(int arr[], int size, int key) {
    int step = sqrt(size);
    int prev = 0;

    while (arr[min(step, size)] < key) {
        prev = step;
        step += sqrt(size);
        if (prev >= size) return -1;

    }

    for (int i = prev; i < min(step, size); ++i) {
        if (arr[i] == key) return i;
    }
    return -1;
}


//Random Search
int randomSearch(int arr[], int size, int key) {
    int* indices = new int[size];
    for(int i = 0; i < size; ++i) {
        indices[i] = i;
    }

    for (int i = size - 1; i >0; --i) {
        int j = rand() % (i + 1);
        swap(indices[i], indices[j]);
    }

    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            return i;
            delete[] indices;
        }
    }
    delete[] indices;
    return -1;

}
void generateSortedArray(int* arr, int n, int range) {
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % range;
    }
    sort(arr, arr + n);
}


int main() {
    srand(time(0));

    const int numSizes = 3;
    int sizes[numSizes] = {1000, 10000, 100000}; // Example sizes
    int rangeMultiplier = 10;

    for (int s = 0; s < numSizes; ++s) {
        int n = sizes[s];
        int* arr = new int[n];
        generateSortedArray(arr, n, n * rangeMultiplier);

        for (int scenario = 0; scenario < 4; ++scenario) {
            int key;
            switch (scenario) {
                case 0: key = arr[0]; break;                // Close to beginning
                case 1: key = arr[n / 2]; break;            // Around middle
                case 2: key = arr[n - 1]; break;           // Close to end
                case 3: key = -1; break;                   // Key does not exist
            }

            cout << "Array Size: " << n << ", Scenario: " << scenario << endl;



            double duration;
            clock_t startTime = clock();
            cout << linearSearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;


            startTime = clock();
            cout << linearSearchRecursive(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;



            //With a single code, time of binary search comes 0. To take average of time, binary search will work 7 times for each scenario.
            startTime = clock();
            cout << binarySearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;

            startTime = clock();
            cout << binarySearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;


            startTime = clock();
            cout << binarySearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;

            startTime = clock();
            cout << binarySearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;

            startTime = clock();
            cout << binarySearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;

            startTime = clock();
            cout << binarySearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;

            startTime = clock();
            cout << binarySearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;




            cout << endl;



            //With a single code, time of jump search comes 0. To take average of time, jump search will work 7 times for each scenario.

            startTime = clock();
            cout << linearSearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;

            startTime = clock();
            cout << linearSearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;

            startTime = clock();
            cout << linearSearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;

            startTime = clock();
            cout << linearSearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;

            startTime = clock();
            cout << linearSearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;

            startTime = clock();
            cout << linearSearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;

            startTime = clock();
            cout << linearSearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;



            cout << endl;

            startTime = clock();
            cout << randomSearch(arr, n, key) << endl;
            duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
            cout << "Execution took " << duration << " milliseconds." << endl;




        }
        delete[] arr;

    }
    return 0;
}