#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#include "Mylib.h"
#include <vector>
#include <string>
#include <algorithm> // for std::swap
#include <cstring>   // for std::strlen, std::memcpy

class Studentas {
private:
    char* vardas;
    char* pavarde;
    std::vector<int> tarpRez;
    int egzamRez;
    double vidurkis;
    double mediana;
    double galutinis;

    void copyString(char*& dest, const char* src);

public:
    Studentas(const char* v = nullptr, const char* p = nullptr);
    ~Studentas();
    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);

    const char* getVardas() const;
    void setVardas(const char* name);
    void setVardas(const std::string& name);
    const char* getPavarde() const;
    void setPavarde(const char* surname);
    void setPavarde(const std::string& surname);
    const std::vector<int>& getTarpRez() const;
    void setTarpRez(const std::vector<int>& grades);
    int getEgzamRez() const;
    void setEgzamRez(int egzaminas);
    double getGalutinis() const;
    void setGalutinis(double finalGrade);

    double calculateVidurkis() const;
    double calculateMediana() const;
    void clean();
};

void inputManual(Studentas& Lok);
void inputScan(std::vector<Studentas>& studentai);
void outputManual(const Studentas& Lok, int vidMed);
void outputScan(std::vector<Studentas>& studentai);
void generate(int studGenSk, int ndGenSk, int containerChoice);

template <typename Container>
void inputScanSort1(std::string failoPav, int rusiavKateg);

template <typename Container>
void inputScanSort2(std::string failoPav, int rusiavKateg);

template <typename Container>
void inputScanSort3(std::string failoPav, int rusiavKateg);

#endif
