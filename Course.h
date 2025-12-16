#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include "Attendance.h"
#include "Assignment.h"

using namespace std;

class Course {
private:
    static const int max = 100;
    Attendance* attendanceLog[max];
    int attendanceCount;

    Assignment* assignmentList[max];
    int assignmentCount;

public:
    string courseCode;
    string courseName;
    string section;
    int credits;

    Course(string code, string name, string sec, int cr)
        : courseCode(code), courseName(name), section(sec), credits(cr) {
        attendanceCount = 0;
        assignmentCount = 0;
    }

    ~Course() {
        for (int i = 0; i < attendanceCount; i++) {
            delete attendanceLog[i];
        }
    }

    string formatForFile() {
        return "Code: " + courseCode + " | Section: " + section + " | Name: " + courseName;
    }
    void markAttendance(string studentID, Date date, string status) {
        if (attendanceCount < max) {
            attendanceLog[attendanceCount] = new Attendance(studentID, date, status);
            attendanceCount++;
            cout << "Success: Attendance marked for " << studentID << endl;
        }
        else {
            cout << "Error: Log full." << endl;
        }
    }

    void displayAttendance(string studentID) {
        cout << "Attendance Record for " << studentID << " in " << courseCode << " (" << section << "):" << endl;
        bool found = false;
        for (int i = 0; i < attendanceCount; i++) {
            if (attendanceLog[i]->studentID == studentID) {
                cout << attendanceLog[i]->formatForFile() << endl;
                found = true;
            }
        }
        if (!found) cout << "No records found." << endl;
    }
    void addAssignment(Assignment* assign) {
        if (assignmentCount < max) {
            assignmentList[assignmentCount] = assign;
            assignmentCount++;
            cout << "Success: Assignment '" << assign->title << "' uploaded." << endl;
        }
        else {
            cout << "Error: Assignment list full." << endl;
        }
    }

    void displayAssignments() {
        cout << "Assignments for " << courseCode << " (" << section << "):" << endl;
        for (int i = 0; i < assignmentCount; i++) {
            cout << assignmentList[i]->formatForFile() << endl;
        }
    }
};

#endif
