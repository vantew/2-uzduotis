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
   
2. Duomenu isvestis:
  * Metodas: outputManual(const Studentas& student, int vidMed)
    - Aprasymas: Duomenys isvedami i konsole.
  * Metodas: outputScan(std::vector<Studentas>& studentai)
    - Aprasymas: Sistema taip pat gali issaugoti studentu duomenis ir skaiciavimus i faila.
   
3. Skaiciavimai:
  * Sistema apskaiciuoja vidurki ir medianą pagal studentu pazymius.

4. Rusiavimo Parinktys:
  * Studentai gali buti rusiuojami pagal skirtingus kriterijus, pagal varda, pavarde arba vidurkio pazymi.

5. Rule of Three:
  * Kodas tinkamai vykdo dinamini atminties valdyma su kopijavimo konstruktoriais, kopijavimo priskyrimo operatoriais ir destruktoriais, kad butu isvengta atminties nuotekiu kopijuojant objektus.

Spartos analizes atlikimo rezultatai:
* Tegu programa priima daug ivairiu tipo duomenu, tuo tikslu pasirinkus analizuoti 1000000 ir 10000000 duomenu irasu failus ir palyginus 3 strategijas aptartas senesniuose release'uose, galima matyti, jog Struct veikia zymiai greiciau siame projekte:
<img width="1208" alt="Screenshot 2024-11-26 at 21 16 29" src="https://github.com/user-attachments/assets/598705f6-20db-407f-9718-0e7b3ca6c713">

Eksperimentine analize lyginant kompiliatoriu optimizavimo lygius pasirinkus 1000000 ir 10000000 duomenu irasu failus:
<img width="1626" alt="Screenshot 2024-11-26 at 22 17 41" src="https://github.com/user-attachments/assets/b24e643c-eb42-4f6e-9dde-5635620a6174">


