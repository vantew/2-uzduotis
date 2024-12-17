#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#include "Mylib.h"
#include "Zmogus.h"

class Studentas : public Zmogus {
private:
    int egzamRez;
    double vidurkis;
    double mediana;
    double galutinis;
    vector<int> tarpRez;
    list<int> tarpRezlist;
    int containerChoice;

    static char* deepCopy(const char* source);

public:
    Studentas();
    ~Studentas();
    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);

    int getEgzamRez() const;
    void setEgzamRez (int egzaminas) {
        egzamRez = egzaminas;
    }

    double getGalutinis() const;
    void setGalutinis(double finalGrade);

    int getContainerChoice() const;
    void setContainerChoice(int choice);

    template <typename Container>
    const Container& getTarpRez() const;

    template <typename Container>
    void setTarpRez(const Container& grades) {
        tarpRez.assign(grades.begin(), grades.end());

        if (!tarpRez.empty()) {
            galutinis = (accumulate(tarpRez.begin(), tarpRez.end(), 0.0) + egzamRez) / (tarpRez.size() + 1);
        }
    }

    template <typename Container>
    double calculateVidurkis(const Container& grades) const;

    template <typename Container>
    double calculateMediana(const Container& grades) const;

    friend ostream& operator<<(ostream& os, const Studentas& Lok);
    friend istream& operator>>(istream& is, Studentas& Lok);

    void reset() override {
        tarpRez.clear();
        tarpRezlist.clear();
        egzamRez = 0;
        vidurkis = 0.0;
        mediana = 0.0;
        galutinis = 0.0;
    }
};

template <typename Container>
double Studentas::calculateVidurkis(const Container& grades) const {
    if (grades.empty()) return 0.0;
    double sum = accumulate(grades.begin(), grades.end(), 0.0);
    return sum / grades.size();
}

template <typename Container>
void inputManual(Studentas &Lok, Container &grades, int containerChoice);

template <typename Container>
void inoutScan(Container& visiStudentai);

void outputManual(const Studentas& Lok, int vidMed);

void generate(int studGenSk, int ndGenSk);

template <typename Container>
void inputScanSort1(string failoPav, int rusiavKateg);

template <typename Container>
void inputScanSort2(string failoPav, int rusiavKateg);

template <typename Container>
void inputScanSort3(string failoPav, int rusiavKateg);



#endif
