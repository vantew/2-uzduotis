Studentu App'sas
Programa veikia nuo C++17
Sis projektas yra studentu ivedimo sistema, kuri leidzia skirtingais budais ivesti studentus ir ju pazymius, suskaiciuoja bei isveda studentu vidurki ir mediana, o be to, leidzia pasirinkti pagal ka rikiuoti spausdintus studentus. 

Funkcijos:
1. Duomenu ivedimas:
  * Metodas: void inputManual(Studentas& student)
    - Aprasymas: Sis metodas leidzia vartotojui rankiniu budu ivesti studento duomenis, tokius kaip vardas, pavarde, pazymiai .
  * Metodas: generate(int studentuSkaičius, int pazymiuSkaičius, int konteinerioTipas)
    - Aprasymas: vartotojas gali pasirinkti atsitiktinai sugeneruoti ivesto studento pazymius
  * Metodas: inputScan(std::vector<Studentas>& studentai) arba inputScan(std::list<Studentas>& studentai)
    - Aprasymas: pasirinkimas nuskaityti studentu duomenis is failo.
   
3. Duomenu isvestis:
  * Metodas: outputManual(const Studentas& student, int vidMed)
    - Aprasymas: Duomenys isvedami i konsole.
  * Metodas: outputScan(std::vector<Studentas>& studentai)
    - Aprasymas: Sistema taip pat gali issaugoti studentu duomenis ir skaiciavimus i faila.
   
4. Skaiciavimai:
  * Sistema apskaiciuoja vidurki ir medianą pagal studentu pazymius.

6. Rusiavimo Parinktys:
  * Studentai gali buti rusiuojami pagal skirtingus kriterijus, pagal varda, pavarde arba vidurkio pazymi.

7. Rule of Three:
  * Kodas tinkamai vykdo dinamini atminties valdyma su kopijavimo konstruktoriais, kopijavimo priskyrimo operatoriais ir destruktoriais, kad butu isvengta atminties nuotekiu kopijuojant objektus.

