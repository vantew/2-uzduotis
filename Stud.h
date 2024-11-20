#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#include "Mylib.h"

struct Studentas{
    string vardas;
    string pavarde;
    vector<int> tarpRez;
    int egzamRez;
    double vidurkis, mediana;
    vector<int> balai;
    double galutinis;
};

void inputManual(Studentas &Lok);
void inputScan(vector<Studentas> &studentai);
void outputManual(const Studentas& Lok, int vidMed);
void outputScan(vector<Studentas> &studentai);
void clean(Studentas &Lok);
void generate(int studGenSk, int ndGenSk, int containerChoice);
template <typename Container>
void inputScanSort1(string failoPav, int rusiavKateg);
template <typename Container>
void inputScanSort2(string failoPav, int rusiavKateg);
template <typename Container>
void inputScanSort3(string failoPav, int rusiavKateg);



#endif
