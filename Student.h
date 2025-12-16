#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "Dashboard.h"

class Student : public User {
public:
    Student(string n, string pass, Date d) : User(n, pass, d) {}

    void viewDashboard() {
        Dashboard d;
        d.viewNotifications();
    }

    void viewAll() {
        int choice;
        do {
            cout << "\n[STUDENT] 1. Attendance 2. Seating Plan 3. Results 4. Fee Challan 5. Assignments 6. Dashboard 7. Logout\nChoice: ";
            cin >> choice;
            if (choice == 1) readFile("Attendance.txt");
            else if (choice == 2) readFile("SeatingPlan.txt");
            else if (choice == 3) readFile("Results.txt");
            else if (choice == 4) readFile("FeeChallan.txt");
            else if (choice == 5) readFile("Assignments.txt");
            else if (choice == 6) viewDashboard();
        } while (choice != 7);
    }
};

#endif
