#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <iostream>
#include <string>
#include "Date.h"
using namespace std;

class Attendance {
public:
    string studentID;
    Date date;
    string status;

    Attendance(string id, Date d, string s) : studentID(id), date(d), status(s) {}

    string formatForFile() {
        return "Date: " + date.toString() + " | Student: " + studentID + " | Status: " + status;
    }
};

#endif
