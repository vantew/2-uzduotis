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
    Studentas();
    ~Studentas();

    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);

    const std::string& getVardas() const;
    void setVardas(const std::string& name);

    const std::string& getPavarde() const;
    void setPavarde(const std::string& surname);

    const std::vector<int>& getTarpRez() const;
    void setTarpRez(const std::vector<int>& grades);

    int getEgzamRez() const;
    void setEgzamRez(int egzaminas);

    double getGalutinis() const;
    void setGalutinis(double finalGrade);

    double calculateVidurkis() const;
    double calculateMediana() const;

    friend std::ostream& operator<<(std::ostream& os, const Studentas& Lok);
    //friend std::istream& operator>>(std::istream& is, Studentas& Lok);


    void reset();

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
