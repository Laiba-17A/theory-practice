#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Custom exception class
class Bot_Exception {
    string message;
public:
    Bot_Exception(string msg) : message(msg) {}
    string what() { return message; }
};

// Forward declaration
class User;

// Base Chatbot class
class Chatbot {
protected:
    int total_users;
    string last_user;
public:
    Chatbot() { total_users = 0; }

    virtual string generate_response(string query, User u) = 0;

    void update_user(string username) {
        last_user = username;
        total_users++;
    }

    int get_user_count() {
        return total_users;
    }
};

// User class
class User {
public:
    string username, country, interest;
    int age;

    User(string uname, string c, string i, int a) {
        username = uname;
        country = c;
        interest = i;
        age = a;
    }

    string Ask(string query);
};

// Chatbot variants
class MedicalChatbot : public Chatbot {
public:
    string generate_response(string query, User u) {
        update_user(u.username);
        return "Hi " + u.username + ", this is your medical advice.";
    }
};

class LegalChatbot : public Chatbot {
public:
    string generate_response(string query, User u) {
        update_user(u.username);
        return "Hi " + u.username + ", this is your legal advice.";
    }
};

class TechnologyChatbot : public Chatbot {
public:
    string generate_response(string query, User u) {
        update_user(u.username);
        return "Hi " + u.username + ", here’s your tech insight.";
    }
};

class GeneralChatbot : public Chatbot {
public:
    string generate_response(string query, User u) {
        update_user(u.username);
        return "Hi " + u.username + ", how can I help you today?";
    }
};

// Global chatbot instances
MedicalChatbot med;
LegalChatbot legal;
TechnologyChatbot tech;
GeneralChatbot gen;

// Log error
void log_error(string username, string query) {
    ofstream fout("error_log.txt", ios::app);
    fout << username << " : " << query << endl;
    fout.close();
}

// User's Ask method
string User::Ask(string query) {
    string prefix = query.substr(0, query.find(' '));

    try {
        if (prefix == "doc") return med.generate_response(query, *this);
        else if (prefix == "attorney") return legal.generate_response(query, *this);
        else if (prefix == "guru") return tech.generate_response(query, *this);
        else if (prefix == "special") {
            if (interest == "medical") return med.generate_response(query, *this);
            else if (interest == "legal") return legal.generate_response(query, *this);
            else if (interest == "technology") return tech.generate_response(query, *this);
            else return gen.generate_response(query, *this);
        } else {
            throw Bot_Exception("Invalid query prefix");
        }
    } catch (Bot_Exception &e) {
        log_error(username, query);
        return "Error: " + e.what();
    }
}

// Simple analysis
void Analysis() {
    ifstream fin("error_log.txt");
    string line;
    string usernames[100];
    int counts[100] = {0};
    int index = 0;

    while (getline(fin, line)) {
        string uname = line.substr(0, line.find(':'));
        bool found = false;

        for (int i = 0; i < index; i++) {
            if (usernames[i] == uname) {
                counts[i]++;
                found = true;
                break;
            }
        }

        if (!found) {
            usernames[index] = uname;
            counts[index] = 1;
            index++;
        }
    }
    fin.close();

    int maxIndex = 0;
    for (int i = 1; i < index; i++) {
        if (counts[i] > counts[maxIndex]) maxIndex = i;
    }

    cout << "User with most exceptions: " << usernames[maxIndex] << " (" << counts[maxIndex] << " errors)" << endl;

    // Word count per user
    ifstream fin2("error_log.txt");
    string line2;
    while (getline(fin2, line2)) {
        string uname = line2.substr(0, line2.find(':'));
        string query = line2.substr(line2.find(':') + 1);
        int word_count = 1;
        for (int i = 0; i < query.length(); i++) {
            if (query[i] == ' ') word_count++;
        }
        cout << uname << ": " << word_count << " words" << endl;
    }
    fin2.close();
}

// Main
int main() {
    User u1("Alice", "USA", "technology", 28);
    User u2("Bob", "UK", "medical", 35);
    User u3("Charlie", "India", "legal", 40);

    cout << u1.Ask("guru What is AI?") << endl;
    cout << u2.Ask("doc I have a headache") << endl;
    cout << u3.Ask("attorney Help needed") << endl;
    cout << u1.Ask("special Suggest a tool") << endl;
    cout << u2.Ask("hello Unknown format") << endl;

    Analysis();

    return 0;
}
