#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Dashboard {
public:
    void addNotification(string note) {
        ofstream outFile("Notifications.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "[Notification] " << note << endl;
            outFile.close();
        }
    }

    void viewNotifications() {
        ifstream inFile("Notifications.txt");
        string line;
        cout << "\n--- DASHBOARD NOTIFICATIONS ---\n";
        if (!inFile) { cout << "No notifications.\n"; return; }
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        cout << "-------------------------------\n";
    }
};

#endif
