#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <iostream>
#include <string>
#include "Date.h"
using namespace std;

class Assignment {
public:
    string title;
    int totalMarks;
    Date dueDate;

    Assignment(string t, int marks, Date d) : title(t), totalMarks(marks), dueDate(d) {}

    string formatForFile() {
        return "Title: " + title + " | Marks: " + to_string(totalMarks) + " | Due: " + dueDate.toString();
    }
};

#endif
