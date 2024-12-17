#include "Mylib.h"
#include "Zmogus.h"

char* Zmogus::deepCopy(const char* source) {
    if (!source) return nullptr;
    char* copy = new char[strlen(source) + 1];
    strcpy(copy, source);
    return copy;
}

Zmogus::Zmogus() : vardas(nullptr), pavarde(nullptr) {}

Zmogus::Zmogus(const string& name, const string& surname) {
    vardas = deepCopy(name.c_str());
    pavarde = deepCopy(surname.c_str());
}

Zmogus::~Zmogus() {
    delete[] vardas;
    delete[] pavarde;
}

Zmogus::Zmogus(const Zmogus& other) {
    vardas = deepCopy(other.vardas);
    pavarde = deepCopy(other.pavarde);
}

Zmogus& Zmogus::operator=(const Zmogus& other) {
    if (this != &other) {
        delete[] vardas;
        delete[] pavarde;
        vardas = deepCopy(other.vardas);
        pavarde = deepCopy(other.pavarde);
    }
    return *this;
}

const char* Zmogus::getVardas() const { return vardas; }
void Zmogus::setVardas(const string& name) {
    delete[] vardas;
    vardas = deepCopy(name.c_str());
}

const char* Zmogus::getPavarde() const { return pavarde; }
void Zmogus::setPavarde(const string& surname) {
    delete[] pavarde;
    pavarde = deepCopy(surname.c_str());
}

void Zmogus::reset() {
    delete[] vardas;
    delete[] pavarde;
    vardas = nullptr;
    pavarde = nullptr;
}
