#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#include "Mylib.h"

class Studentas {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> tarpRez;
    int egzamRez;
    double vidurkis;
    double mediana;
    double galutinis;

public:
    // Constructor
    Studentas();

    // Getters and Setters
    const std::string& getVardas() const;
    void setVardas(const std::string&);

    const std::string& getPavarde() const;
    void setPavarde(const std::string&);

    const std::vector<int>& getTarpRez() const;
    void setTarpRez(const std::vector<int>& grades) {
        tarpRez = grades;
    }

    int getEgzamRez() const;
    void setEgzamRez(int);

    double getGalutinis() const;
    void setGalutinis(double);

    // Member functions
    double calculateVidurkis() const;
    double calculateMediana() const;
    void clean();
};

// Free functions
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
