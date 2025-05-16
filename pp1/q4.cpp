#include <iostream>
#include <stdexcept>
using namespace std;

// Helper function to calculate Greatest Common Divisor (GCD)
int gcd(int a, int b) {
    if (b == 0) return abs(a);
    return gcd(b, a % b);
}

class RationalNumber {
private:
    int numerator;
    int denominator;

    void simplify() {
        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        // Keep denominator positive
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // Constructor
    RationalNumber(int num = 0, int den = 1) {
        if (den == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        }
        numerator = num;
        denominator = den;
        simplify();
    }

    // Addition operator
    RationalNumber operator+(const RationalNumber& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int den = denominator * other.denominator;
        return RationalNumber(num, den);
    }

    // Friend function for division
    friend RationalNumber operator/(const RationalNumber& lhs, const RationalNumber& rhs);

    // Equality operator
    bool operator==(const RationalNumber& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    // Output (<<) operator
    friend ostream& operator<<(ostream& os, const RationalNumber& obj);
};

// Definition of friend division operator
RationalNumber operator/(const RationalNumber& lhs, const RationalNumber& rhs) {
    if (rhs.numerator == 0) {
        throw domain_error("Division by zero.");
    }
    int num = lhs.numerator * rhs.denominator;
    int den = lhs.denominator * rhs.numerator;
    return RationalNumber(num, den);
}

// Definition of friend output operator
ostream& operator<<(ostream& os, const RationalNumber& obj) {
    if (obj.denominator == 1)
        os << obj.numerator;
    else
        os << obj.numerator << "/" << obj.denominator;
    return os;
}

// Main function to test the class
int main() {
    try {
        RationalNumber obj1(3, 5), obj2(5, 25), result;
        cout<<obj2<<endl;
        result = obj1 + obj2;
        cout << "Addition result: " << result << endl;

        result = obj1 / obj2;
        cout << "Division result: " << result << endl;

        cout << "Equality check: " << boolalpha << (obj1 == obj2) << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
