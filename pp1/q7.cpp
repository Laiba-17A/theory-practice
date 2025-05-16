#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class LargestFinder {
    T* arr;
    int size;

public:
    LargestFinder(T* a, int s) : arr(a), size(s) {}

    T largest() {
        T max = arr[0];
        for (int i = 1; i < size; i++)
            if (arr[i] > max)
                max = arr[i];
        return max;
    }

    T secondLargest() {
        T max = arr[0], second;
        bool found = false;

        // First, find the largest
        for (int i = 1; i < size; i++)
            if (arr[i] > max)
                max = arr[i];

        // Then find the second largest
        for (int i = 0; i < size; i++) {
            if (arr[i] != max) {
                if (!found || arr[i] > second) {
                    second = arr[i];
                    found = true;
                }
            }
        }

        if (!found)
            throw runtime_error("No distinct second largest element found.");

        return second;
    }
};

int main() {
    int arr[] = {1,6,10,9,40,3};
    int n = sizeof(arr) / sizeof(arr[0]);

    LargestFinder<int> finder(arr, n);

    try {
        cout << "Largest: " << finder.largest() << endl;
        cout << "Second Largest: " << finder.secondLargest() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}

