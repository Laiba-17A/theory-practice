#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Create and initialize vector
    vector<int> v = {10, 20, 30};

    // Add elements
    v.push_back(40);
    v.push_back(50);

    // Display elements using for loop
    cout << "Vector elements: ";
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";
    cout << endl;

    // Access front and back
    cout << "Front: " << v.front() << endl;
    cout << "Back: " << v.back() << endl;

    // Size and capacity
    cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << endl;

    // Insert at position 2
    v.insert(v.begin() + 2, 25);

    // Erase element at position 3
    v.erase(v.begin() + 3);

    // Display after insert and erase
    cout << "After insert and erase: ";
    for (int x : v)
        cout << x << " ";
    cout << endl;

    // Check if vector is empty
    cout << "Is empty? " << (v.empty() ? "Yes" : "No") << endl;

    // Pop last element
    v.pop_back();

    // Resize vector to 3 elements
    v.resize(3);

    // Clear vector
    v.clear();

    // Final state
    cout << "Final size: " << v.size() << ", Is empty? " << (v.empty() ? "Yes" : "No") << endl;

    return 0;
}
