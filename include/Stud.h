#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#include "Mylib.h"

class Studentas {
private:
    char* vardas;                // Dynamically allocated name
    char* pavarde;               // Dynamically allocated surname
    int egzamRez;                // Exam grade
    double vidurkis;             // Average
    double mediana;              // Median
    double galutinis;
    std::vector<int> tarpRez;
    std::list<int> tarpRezlist;
    int containerChoice;         // Final grade

    // Helper function for deep copying a C-string
    static char* deepCopy(const char* source);

public:
    // Default Constructor
    Studentas();

    // Destructor
    ~Studentas();

    // Copy Constructor
    Studentas(const Studentas& other);

    // Copy Assignment Operator
    Studentas& operator=(const Studentas& other);

    // Getter and Setter for vardas
    const char* getVardas() const;
    void setVardas(const std::string& name);

    // Getter and Setter for pavarde
    const char* getPavarde() const;
    void setPavarde(const std::string& surname);

    // Getter and Setter for egzamRez
    int getEgzamRez() const;
    void setEgzamRez(int egzaminas);

    // Getter and Setter for galutinis
    double getGalutinis() const;
    void setGalutinis(double finalGrade);

    // Getter and Setter for containerChoice
    int getContainerChoice() const;
    void setContainerChoice(int choice);

    template <typename Container>
    const Container& getTarpRez() const;

    // Template calculation methods for compatibility with vector or list
    template <typename Container>
    void setTarpRez(const Container& grades);

    template <typename Container>
    double calculateVidurkis(const Container& grades) const;

    template <typename Container>
    double calculateMediana(const Container& grades) const;

    // Stream Operators
    friend std::ostream& operator<<(std::ostream& os, const Studentas& Lok);
    friend std::istream& operator>>(std::istream& is, Studentas& Lok);

    // Reset Method
    void reset();
};


template <typename Container>
void inputManual(Studentas &Lok, Container &grades, int containerChoice);
template <typename Container>
void inputScan(Container& studentai);

void outputManual(const Studentas& Lok, int vidMed);

template <typename Container>
void outputScan(Container &studentai);

void generate(int studGenSk, int ndGenSk);

template <typename Container>
void inputScanSort1(std::string failoPav, int rusiavKateg);

template <typename Container>
void inputScanSort2(std::string failoPav, int rusiavKateg);

template <typename Container>
void inputScanSort3(std::string failoPav, int rusiavKateg);

#endif
