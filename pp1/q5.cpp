#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Convert "hh/mm/ss" to seconds
int convertToSeconds(const string& timeStr) {
    int h, m, s;
    char sep1, sep2;
    stringstream ss(timeStr);

    ss >> h >> sep1 >> m >> sep2 >> s;

    if (!ss || sep1 != '/' || sep2 != '/' || h < 0 || m < 0 || m > 59 || s < 0 || s > 59) {
        throw invalid_argument("Invalid time format or values.");
    }

    return h * 3600 + m * 60 + s;
}

// Global function to validate roll target
void validateRollTarget(int n) {
    if (n < 2 || n > 12) {
        throw invalid_argument("Roll target must be between 2 and 12.");
    }
}

// Class for rolling dice until sum == N
class rollFor {
    int numberOfRolls;
    int N;

public:
    rollFor(int target) {
        N = target;
        numberOfRolls = 0;
    }

    void simulate() {
        srand(time(0));
        int die1, die2;
        do {
            die1 = rand() % 6 + 1;
            die2 = rand() % 6 + 1;
            numberOfRolls++;
        } while (die1 + die2 != N);

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

        validateRollTarget(target);    // Call global validation function

        rollFor roller(target);
        roller.simulate();
        roller.display();
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
