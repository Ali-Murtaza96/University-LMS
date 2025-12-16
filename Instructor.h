#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <iostream>
#include <string>
#include "User.h"
#include "Assignment.h"
#include "Attendance.h"
#include "Course.h"

using namespace std;

class Instructor : public User {
public:
    Instructor(string n, string pass, Date d) : User(n, pass, d) {}

    Course* createNewCourse() {
        string code, name, section;
        int credits;

        cout << "\n--- Enter Course Details ---" << endl;
        cout << "Enter Course Code: "; cin >> code;

        cin.ignore();
        cout << "Enter Course Name: "; getline(cin, name);

        cout << "Enter Section: "; cin >> section;
        cout << "Enter Credits: "; cin >> credits;

        return new Course(code, name, section, credits);
    }

    void uploadAssignment(Course* course) {
        string title;
        int marks; int D, M, Y;
        char c;
        cout << "Title: "; cin.ignore(); getline(cin, title);
        cout << "Total Marks: "; cin >> marks;
        cout << "Due Date (D / M / Y): "; cin >> D >> c >> M >> c >> Y;

        Assignment* asg = new Assignment(title, marks, Date(D, M, Y));
        course->addAssignment(asg);
    }

    void markAttendance(Course* course) {
        string id, status;
        int D, M, Y;
        char c;
        cout << "Student ID: "; cin >> id;
        cout << "Date (D / M / Y): "; cin >> D >> c >> M >> c >> Y;
        cout << "Status (P/A): "; cin >> status;
        course->markAttendance(id, Date(D, M, Y), status);
    }

    void instructorMenu(Course* course) {
        int choice;
        do {
            cout << "\n[INSTRUCTOR MENU for " << course->courseCode << "]" << endl;
            cout << "1. Upload Assignment\n2. Mark Attendance\n3. Logout\nChoice: ";
            cin >> choice;

            if (choice == 1) {
                uploadAssignment(course);
            }
            else if (choice == 2) {
                markAttendance(course);
            }
        } while (choice != 3);
    }
};

#endif
