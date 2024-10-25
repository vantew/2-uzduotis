#ifndef STUD_H_INCLUDED
#define STUD_H_INCLUDED

#include "Mylib.h"

struct Stud {
    string name, surname;
    vector<double> HW;
    double avg, exam, med;
};

void input(Stud &Lok, int hwCount);
void inputgrades(Stud &Lok);
void inputnull(Stud &Lok);
void readfile(const string &line, Stud &Lok);
void randomgrades(Stud &Lok, int hwCount);
void outputnull(Stud Lok);
void outputfile(ofstream &outfile, Stud Lok);
void outputavg(Stud Lok);
void outputmed(Stud Lok);
void clean(Stud &Lok);
void printHeaderfile(ofstream &outfile);
void printHeaderavg();
void printHeadermed();
void printHeadernull();
double calculateMedian(vector<double>& grades);
void sortsurname(vector<Stud> &students);

void filegeneration(const string& filename, int numEntries, int numHW, vector<Stud>& Vec1);
void filterandsave(char filteroption, const string& studentinput, const string& below5file, const string& above5file);
void readfile(const string &inputfile, vector<Stud> &allstudents);
void filterbelow5(const vector<Stud> &allstudents, vector<Stud> &below5);
void filterabove5(const vector<Stud> &allstudents, vector<Stud> &above5);
void savetofile(const string &filename, const vector<Stud> &students);
void filetimer(const std::string &filename, int size, int numHW, std::vector<Stud> &Vec1, int filteroption);
void outputbelow5file(ofstream& belowfile, const vector<Stud>& below5);
void outputabove5file(ofstream& belowfile, const vector<Stud>& above5);

void filegenerationList(const string& filename, int numEntries, int numHW, list<Stud>& List1);
void filterbelow5List(const list<Stud>& allstudents, list<Stud>& below5);
void filterabove5List(const list<Stud>& allstudents, list<Stud>& above5);
void readfileList(const string &inputfile, list<Stud> &allstudents);
void savetofileList(const string &filename, const list<Stud> &students);
void filetimerList(const string &filename, int size, int numHW, list<Stud> &List1, char filteroption);

#endif // STUD_H_INCLUDED
