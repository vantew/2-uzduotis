#ifndef STUD_H_INCLUDED
#define STUD_H_INCLUDED

#include "Mylib.h"

struct Stud {
    string name, surname;
    vector<double> HW;
    double avg, exam, med, rez;
};

void input(Stud &Lok, int hwCount);
void inputgrades(Stud &Lok);
void outputavg(Stud Lok);
void outputmed(Stud Lok);
void clean(Stud &Lok);
void printHeaderavg();
void printHeadermed();
double calculateMedian(vector<double>& grades);

#endif // STUD_H_INCLUDED
