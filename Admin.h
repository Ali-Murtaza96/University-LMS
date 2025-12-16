#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "FeeChallan.h"
#include "Dashboard.h"

class Admin : public User {
public:
    Admin(string n, string pass, Date d) : User(n, pass, d) {}

    void manageDashboard() {
        string note;
        cout << "Enter new notification for Dashboard: ";
        cin.ignore(); getline(cin, note);
        Dashboard d;
        d.addNotification(note);
    }

    void generateFeeChallan() {
        string id; int amt; int D, M, Y;
        char c;
        cout << "Student ID: "; cin >> id;
        cout << "Amount: "; cin >> amt;
        cout << "Due Date (D / M / Y): "; cin >> D >>c>> M >>c>> Y;

        FeeChallan fc(id, amt, Date(D, M, Y));
        appendFile("FeeChallan.txt", fc.formatForFile());
    }

    void uploadExamSeatingPlan() {
        string plan;
        cout << "Enter Seating Plan details: ";
        cin.ignore(); getline(cin, plan);
        appendFile("SeatingPlan.txt", plan);
    }

    void uploadResults() {
        string res;
        cout << "Enter Result details: ";
        cin.ignore(); getline(cin, res);
        appendFile("Results.txt", res);
    }

    void adminMenu() {
        int choice;
        do {
            cout << "\n[ADMIN] 1. Fee Challan 2. Seating Plan 3. Results 4. Update Dashboard 5. Logout\nChoice: ";
            cin >> choice;
            if (choice == 1) generateFeeChallan();
            else if (choice == 2) uploadExamSeatingPlan();
            else if (choice == 3) uploadResults();
            else if (choice == 4) manageDashboard();
        } while (choice != 5);
    }
};

#endif
