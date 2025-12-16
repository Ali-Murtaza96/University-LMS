#ifndef FEECHALLAN_H
#define FEECHALLAN_H

#include <iostream>
#include <string>
#include "Date.h"
using namespace std;

class FeeChallan {
public:
    string studentID;
    int amount;
    Date dueDate;
    string status;

    FeeChallan(string id, int amt, Date d) : studentID(id), amount(amt), dueDate(d), status("Unpaid") {}

    string formatForFile() {
        return "Student: " + studentID + " | Amount: " + to_string(amount) + " | Due: " + dueDate.toString() + " | Status: " + status;
    }
};

#endif
