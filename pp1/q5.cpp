#include <iostream>
#include <string>

using namespace std;

// Convert "hh/mm/ss" to seconds using substr
int convertToSeconds(const string& timeStr) {
    if (timeStr.length() != 8 || timeStr[2] != '/' || timeStr[5] != '/')
        throw invalid_argument("Time must be in hh/mm/ss format.");

    int h = stoi(timeStr.substr(0, 2));
    int m = stoi(timeStr.substr(3, 2));
    int s = stoi(timeStr.substr(6, 2));

    if (h < 0 || m < 0 || m > 59 || s < 0 || s > 59)
        throw invalid_argument("Invalid time values.");

    return h * 3600 + m * 60 + s;
}

// Validate roll target
void validateRollTarget(int n) {
    if (n < 2 || n > 12)
        throw invalid_argument("Roll target must be between 2 and 12.");
}

// Class for simulating dice rolls
class rollFor {
    int numberOfRolls;
    int N;

public:
    rollFor(int target) : N(target), numberOfRolls(0) {}

    void simulate() {
        int die1 = 1, die2 = 1;
        while (die1 + die2 != N) {
            die1++;
            if (die1 > 6) {
                die1 = 1;
                die2++;
                if (die2 > 6) die2 = 1;
            }
            numberOfRolls++;
        }

        if (die1 == 1 && die2 == 1)
            cout << "Snake eyes rolled!" << endl;
    }

    void display() const {
        cout << "Number of rolls to get " << N << ": " << numberOfRolls << endl;
    }
};

int main() {
    try {
        cout << "Enter time (hh/mm/ss): ";
        string timeInput;
        cin >> timeInput;

        int seconds = convertToSeconds(timeInput);
        cout << "Total seconds: " << seconds << endl;

        cout << "Enter number to roll for (2-12): ";
        int target;
        cin >> target;

        validateRollTarget(target);

        rollFor roller(target);
        roller.simulate();
        roller.display();
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
