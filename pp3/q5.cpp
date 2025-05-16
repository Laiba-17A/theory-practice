#include <iostream>
#include <fstream>
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

// Abstract Chatbot base class
class Chatbot {
public:
    virtual string generate_response(string query, User u) = 0;
    virtual int get_user_count() = 0;
};

// User class
class User {
public:
    string username, country, interest;
    int age;

    User(string uname, string ctry, string intr, int a) {
        username = uname;
        country = ctry;
        interest = intr;
        age = a;
    }

    string Ask(string query);
};

// Medical Chatbot
class MedicalChatbot : public Chatbot {
    static int instance_count;
    static int user_count;
    static string last_user;
public:
    MedicalChatbot() { instance_count++; }
    string generate_response(string query, User u) override;
    int get_user_count() override { return user_count; }
};
int MedicalChatbot::instance_count = 0;
int MedicalChatbot::user_count = 0;
string MedicalChatbot::last_user = "";

string MedicalChatbot::generate_response(string query, User u) {
    last_user = u.username;
    user_count++;
    return "MedicalBot: Hello " + u.username + ", let's talk about your health.";
}

// Technology Chatbot
class TechnologyChatbot : public Chatbot {
    static int instance_count;
    static int user_count;
    static string last_user;
public:
    TechnologyChatbot() { instance_count++; }
    string generate_response(string query, User u) override;
    int get_user_count() override { return user_count; }
};
int TechnologyChatbot::instance_count = 0;
int TechnologyChatbot::user_count = 0;
string TechnologyChatbot::last_user = "";

string TechnologyChatbot::generate_response(string query, User u) {
    last_user = u.username;
    user_count++;
    return "TechBot: Hello " + u.username + ", let’s explore technology!";
}

// Legal Chatbot
class LegalChatbot : public Chatbot {
    static int instance_count;
    static int user_count;
    static string last_user;
public:
    LegalChatbot() { instance_count++; }
    string generate_response(string query, User u) override;
    int get_user_count() override { return user_count; }
};
int LegalChatbot::instance_count = 0;
int LegalChatbot::user_count = 0;
string LegalChatbot::last_user = "";

string LegalChatbot::generate_response(string query, User u) {
    last_user = u.username;
    user_count++;
    return "LegalBot: Hello " + u.username + ", let’s discuss legal matters.";
}

// General Chatbot
class GeneralChatbot : public Chatbot {
    static int instance_count;
    static int user_count;
    static string last_user;
public:
    GeneralChatbot() { instance_count++; }
    string generate_response(string query, User u) override;
    int get_user_count() override { return user_count; }
};
int GeneralChatbot::instance_count = 0;
int GeneralChatbot::user_count = 0;
string GeneralChatbot::last_user = "";

string GeneralChatbot::generate_response(string query, User u) {
    last_user = u.username;
    user_count++;
    return "GeneralBot: Hi " + u.username + ", I'm here to chat about anything.";
}

// User Ask method implementation
string User::Ask(string query) {
    string prefix = "";
    for (int i = 0; i < query.length(); i++) {
        if (query[i] == ' ') break;
        prefix += query[i];
    }

    try {
        if (prefix == "doc") {
            MedicalChatbot m;
            return m.generate_response(query, *this);
        }
        else if (prefix == "attorney") {
            LegalChatbot l;
            return l.generate_response(query, *this);
        }
        else if (prefix == "guru") {
            TechnologyChatbot t;
            return t.generate_response(query, *this);
        }
        else if (prefix == "special") {
            if (interest == "medical") {
                MedicalChatbot m;
                return m.generate_response(query, *this);
            }
            else if (interest == "technology") {
                TechnologyChatbot t;
                return t.generate_response(query, *this);
            }
            else if (interest == "legal") {
                LegalChatbot l;
                return l.generate_response(query, *this);
            }
            else {
                GeneralChatbot g;
                return g.generate_response(query, *this);
            }
        }
        else {
            throw Bot_Exception("Invalid query format.");
        }
    } catch (Bot_Exception& e) {
        ofstream fout("error_log.txt", ios::app);
        fout << username << "|" << query << endl;
        fout.close();
        return "Error: " + e.what();
    }
}

// Analysis function
void Analysis() {
    ifstream fin("error_log.txt");
    if (!fin.is_open()) {
        cout << "Error log not found.\n";
        return;
    }

    string usernames[100];
    int error_count[100] = {0};
    int user_total = 0;
    int total_words = 0;

    string line;
    while (getline(fin, line)) {
        size_t sep = line.find('|');
        if (sep == string::npos) continue;

        string uname = line.substr(0, sep);
        string query = line.substr(sep + 1);

        // Count words in query
        int word_count = 0;
        for (int i = 0; i < query.length(); i++) {
            if (query[i] == ' ' && i > 0 && query[i-1] != ' ') {
                word_count++;
            }
        }
        if (!query.empty()) word_count++;
        total_words += word_count;

        // Count errors per username
        bool found = false;
        for (int i = 0; i < user_total; i++) {
            if (usernames[i] == uname) {
                error_count[i]++;
                found = true;
                break;
            }
        }
        if (!found) {
            usernames[user_total] = uname;
            error_count[user_total] = 1;
            user_total++;
        }
    }

    // Find max error user
    int max_index = 0;
    for (int i = 1; i < user_total; i++) {
        if (error_count[i] > error_count[max_index]) {
            max_index = i;
        }
    }

    cout << "User with most exceptions: " << usernames[max_index]
         << " (" << error_count[max_index] << " errors)" << endl;
    cout << "Total words in all queries: " << total_words << endl;
}

// Main function for testing
int main() {
    User u1("alice", "USA", "medical", 25);
    User u2("bob", "UK", "technology", 30);
    User u3("carol", "Canada", "fashion", 22);

    cout << u1.Ask("doc I have a headache") << endl;
    cout << u2.Ask("guru tell me about AI") << endl;
    cout << u3.Ask("attorney do I need a license?") << endl;
    cout << u3.Ask("banana this is wrong") << endl;
    cout << u3.Ask("special recommend a dress") << endl;

    cout << "\n=== Error Log Analysis ===\n";
    Analysis();

    return 0;
}

