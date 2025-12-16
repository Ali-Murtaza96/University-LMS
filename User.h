#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <fstream>
#include "Date.h"

using namespace std;

class User {
protected:
    string name;
    string password;
    Date dob;

public:
    User(string n, string pass, Date d) : name(n), password(pass), dob(d) {}

    virtual bool login() {
        string inputPass;
        cout << "Enter Password for " << name << ": ";
        cin >> inputPass;
        if (inputPass == password) return true;
        cout << "Invalid Password.\n";
        return false;
    }

    void appendFile(string filename, string content) {
        ofstream outFile(filename.c_str(), ios::app);
        if (outFile.is_open()) {
            outFile << content << endl;
            cout << "Saved to " << filename << ".\n";
            outFile.close();
        }
        else {
            cout << "Error opening file.\n";
        }
    }

    void readFile(string filename) {
        ifstream inFile(filename.c_str());
        string line;
        cout << "\n--- READING " << filename << " ---\n";
        if (!inFile) { cout << "File empty or not found.\n"; return; }
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        cout << "---------------------------------\n";
    }
};

#endif
