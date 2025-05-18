#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Student {
    int id;          
    string name;
    char gender;
    float quiz1, quiz2, midterm, finalExam;
    float total;

public:
    Student() : id(0), gender(' '), quiz1(0), quiz2(0), midterm(0), finalExam(0), total(0) {}

    Student(int _id, string _name, char _gender, float q1, float q2, float mt, float fe)
        : id(_id), name(_name), gender(_gender), quiz1(q1), quiz2(q2), midterm(mt), finalExam(fe) {
        total = quiz1 + quiz2 + midterm + finalExam;
    }

    int getId() const { return id; }
    float getMidterm() const { return midterm; }
    float getFinal() const { return finalExam; }

    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Gender: " << gender
             << ", Quiz1: " << quiz1 << ", Quiz2: " << quiz2
             << ", Midterm: " << midterm << ", Final: " << finalExam
             << ", Total: " << total << "\n";
    }

    void update(string _name, char _gender, float q1, float q2, float mt, float fe) {
        name = _name;
        gender = _gender;
        quiz1 = q1;
        quiz2 = q2;
        midterm = mt;
        finalExam = fe;
        total = quiz1 + quiz2 + midterm + finalExam;
    }

    void writeToBinary(ofstream &out) const {
        out.write((char*)&id, sizeof(id));

        size_t length = name.size();
        out.write((char*)&length, sizeof(length));
        out.write(name.c_str(), length);

        out.write((char*)&gender, sizeof(gender));
        out.write((char*)&quiz1, sizeof(quiz1));
        out.write((char*)&quiz2, sizeof(quiz2));
        out.write((char*)&midterm, sizeof(midterm));
        out.write((char*)&finalExam, sizeof(finalExam));
        out.write((char*)&total, sizeof(total));
    }

   void readFromBinary(ifstream &in) {
    in.read((char*)&id, sizeof(id));

    size_t length;
    in.read((char*)&length, sizeof(length));

    string temp(length, '\0'); // Create a string with `length` null chars
    in.read(&temp[0], length);      // Read directly into the string's internal buffer
    name = temp;

    in.read((char*)&gender, sizeof(gender));
    in.read((char*)&quiz1, sizeof(quiz1));
    in.read((char*)&quiz2, sizeof(quiz2));
    in.read((char*)&midterm, sizeof(midterm));
    in.read((char*)&finalExam, sizeof(finalExam));
    in.read((char*)&total, sizeof(total));
}

};

vector<Student> loadFromFile(const string& filename) {
    vector<Student> students;
    ifstream in(filename.c_str(), ios::binary);
    if (!in) {
        cout << "File not found, starting with empty list.\n";
        return students;
    }
    size_t count = 0;
    in.read((char*)&count, sizeof(count));
    for (size_t i = 0; i < count; ++i) {
        Student s;
        s.readFromBinary(in);
        students.push_back(s);
    }
    in.close();
    return students;
}

void saveToFile(const string& filename, const vector<Student>& students) {
    ofstream out(filename.c_str(), ios::binary);
    size_t count = students.size();
    out.write((char*)&count, sizeof(count));
    for (const auto& s : students) {
        s.writeToBinary(out);
    }
    out.close();
}

void maxMidterm(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records.\n";
        return;
    }
    const Student* maxStudent = &students[0];
    for (const auto& s : students) {
        if (s.getMidterm() > maxStudent->getMidterm()) {
            maxStudent = &s;
        }
    }
    cout << "\nStudent with highest midterm score:\n";
    maxStudent->display();
}

void averageFinal(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records.\n";
        return;
    }
    float sum = 0;
    for (const auto& s : students) {
        sum += s.getFinal();
    }
    cout << "\nAverage final exam score: " << (sum / students.size()) << "\n";
}

void searchById(const vector<Student>& students, int id) {
    for (const auto& s : students) {
        if (s.getId() == id) {
            cout << "\nStudent found:\n";
            s.display();
            return;
        }
    }
    cout << "\nStudent with ID " << id << " not found.\n";
}

void updateRecord(vector<Student>& students, int id) {
    for (auto& s : students) {
        if (s.getId() == id) {
            string name;
            char gender;
            float q1, q2, mt, fe;
            cout << "Enter new name: ";
            cin >> name;
            cout << "Enter gender (M/F): ";
            cin >> gender;
            cout << "Enter Quiz1, Quiz2, Midterm, Final scores: ";
            cin >> q1 >> q2 >> mt >> fe;
            s.update(name, gender, q1, q2, mt, fe);
            cout << "Record updated successfully.\n";
            return;
        }
    }
    cout << "Student with ID " << id << " not found.\n";
}

int main() {
    string filename = "students.dat";

    vector<Student> students = loadFromFile(filename);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Show student with max midterm score\n";
        cout << "2. Show average final exam score\n";
        cout << "3. Search student by ID\n";
        cout << "4. Update student record\n";
        cout << "5. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                maxMidterm(students);
                break;
            case 2:
                averageFinal(students);
                break;
            case 3: {
                int id;
                cout << "Enter ID: ";
                cin >> id;
                searchById(students, id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter ID to update: ";
                cin >> id;
                updateRecord(students, id);
                break;
            }
            case 5:
                saveToFile(filename, students);
                cout << "Data saved. Exiting.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
