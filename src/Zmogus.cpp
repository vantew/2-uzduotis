#include "Mylib.h"
#include "Zmogus.h"

char* Zmogus::deepCopy(const char* source) {
    if (!source) return nullptr;
    char* copy = new char[strlen(source) + 1];
    strcpy(copy, source);
    return copy;
}

Zmogus::Zmogus() {
    vardas = deepCopy("");
    pavarde = deepCopy("");
}

Zmogus::Zmogus(const std::string& name, const std::string& surname) {
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
        char* newVardas = deepCopy(other.vardas);
        char* newPavarde = deepCopy(other.pavarde);

        // Safely swap only after successful allocation
        delete[] vardas;
        delete[] pavarde;
        vardas = newVardas;
        pavarde = newPavarde;
    }
    return *this;
}


const char* Zmogus::getVardas() const {
    return vardas ? vardas : "";
}

void Zmogus::setVardas(const std::string& name) {
    delete[] vardas;
    vardas = deepCopy(name.c_str());
}

const char* Zmogus::getPavarde() const {
    return pavarde ? pavarde : "";
}

void Zmogus::setPavarde(const std::string& surname) {
    delete[] pavarde;
    pavarde = deepCopy(surname.c_str());
}

void Zmogus::reset() {
    delete[] vardas;
    delete[] pavarde;
    vardas = deepCopy("");
    pavarde = deepCopy("");
}
