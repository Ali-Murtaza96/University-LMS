#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
using namespace std;

class Date {
public:
    int day, month, year;

    Date() : day(1), month(1), year(2023) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
    string toString() {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }
};

#endif
