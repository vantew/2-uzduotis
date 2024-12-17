#include "Mylib.h"
#include "Zmogus.h"

// Helper function
char* Zmogus::deepCopy(const char* source) {
    if (!source) return nullptr;
    char* copy = new char[strlen(source) + 1];
    strcpy(copy, source);
    return copy;
}

// Default constructor
Zmogus::Zmogus() : vardas(nullptr), pavarde(nullptr) {}

// Parameterized constructor
Zmogus::Zmogus(const std::string& name, const std::string& surname) {
    vardas = deepCopy(name.c_str());
    pavarde = deepCopy(surname.c_str());
}

// Destructor
Zmogus::~Zmogus() {
    delete[] vardas;
    delete[] pavarde;
}

// Copy constructor
Zmogus::Zmogus(const Zmogus& other) {
    vardas = deepCopy(other.vardas);
    pavarde = deepCopy(other.pavarde);
}

// Assignment operator
Zmogus& Zmogus::operator=(const Zmogus& other) {
    if (this != &other) {
        delete[] vardas;
        delete[] pavarde;
        vardas = deepCopy(other.vardas);
        pavarde = deepCopy(other.pavarde);
    }
    return *this;
}

// Getters and setters
const char* Zmogus::getVardas() const { return vardas; }
void Zmogus::setVardas(const std::string& name) {
    delete[] vardas;
    vardas = deepCopy(name.c_str());
}

const char* Zmogus::getPavarde() const { return pavarde; }
void Zmogus::setPavarde(const std::string& surname) {
    delete[] pavarde;
    pavarde = deepCopy(surname.c_str());
}

// Reset method
void Zmogus::reset() {
    delete[] vardas;
    delete[] pavarde;
    vardas = nullptr;
    pavarde = nullptr;
}
