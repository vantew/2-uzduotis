#ifndef ZMOGUS_H_INCLUDED
#define ZMOGUS_H_INCLUDED

#include "Mylib.h"

class Zmogus {
protected:
    char* vardas;
    char* pavarde;

    static char* deepCopy(const char* source);

public:
    Zmogus();
    Zmogus(const std::string& name, const std::string& surname);
    virtual ~Zmogus();
    Zmogus(const Zmogus& other);
    Zmogus& operator=(const Zmogus& other);

    const char* getVardas() const;
    void setVardas(const std::string& name);

    const char* getPavarde() const;
    void setPavarde(const std::string& surname);

    virtual void reset() = 0; };

#endif // ZMOGUS_H_INCLUDED
