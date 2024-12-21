Studentu App'sas

Programa veikia nuo C++17

Sis projektas yra studentu ivedimo sistema, kuri leidzia skirtingais budais ivesti studentus ir ju pazymius, suskaiciuoja bei isveda studentu vidurki ir mediana, o be to, leidzia pasirinkti pagal ka rikiuoti spausdintus studentus. 

v0.1
Sukurta programa pagal pradinius reikalavimus, leidžianti:
- Įvesti studento vardą, pavardę, namų darbų ir egzamino rezultatus.
- Suskaičiuoti galutinį balą, remiantis vidurkiu arba mediana.
- Realizuota duomenų nuskaitymo iš failo funkcija.
  
v0.2
- Generuojami penki atsitiktinių studentų sąrašų failai su įrašų skaičiais: 1,000, 10,000, 100,000, 1,000,000 ir 10,000,000.
- Sukurta sistema, leidžianti studentus suskirstyti į dvi kategorijas:
  	* “Vargšiukai”: galutinis balas < 5.0.
  	* “Kietiakiai”: galutinis balas ≥ 5.0.
- Matuojami šie procesai:
	* Failų kūrimas.
 	* Duomenų nuskaitymas iš failų.
	 * Studentų rūšiavimas į kategorijas.
	 * Rezultatų išvedimas į atskirus failus.
   
v0.3
- Pridėtas dviejų konteinerių (std::vector ir std::list) veikimo spartos palyginimas:
	* Studentų rūšiavimas į kategorijas.
	* Duomenų įrašymas į failus.
- Optimizuotas kodas, kad būtų galima lyginti rūšiavimo greitį priklausomai nuo naudojamo konteinerio.
- Išanalizuota, kaip dažnas duomenų šalinimas veikia skirtingus konteinerius.

v1.0
- Optimizuotas studentų rūšiavimo į kategorijas algoritmas, pritaikant tris strategijas:
	* Bendras konteineris skaidomas į du naujus konteinerius.
	* Bendras konteineris skaidomas į vieną naują konteinerį, pašalinant elementus iš pagrindinio.
	* Naudojama efektyviausia pirmų dviejų strategijų versija.
- Įvertinta skirtingų strategijų sparta ir atminties naudojimas.
  
v1.1
- Pakeista duomenų struktūra iš struct į class.
- Palyginta struktūrų ir klasių pagrindu veikiančių programų sparta naudojant:
	* Fiksuotą konteinerį (pvz., std::vector).
	* Greičiausią dalijimo strategiją.
	* Duomenų failus (100,000 ir 1,000,000 įrašų).
- Pridėta eksperimentinė analizė, atsižvelgiant į kompiliatoriaus optimizavimo lygį (-O1, -O2, -O3).
  
v1.2
- Realizuoti "Rule of Three" ir įvesties/išvesties operatoriai Studentas klasei.
- Sukurti operatoriai, kurie gali būti naudingi ateities vartotojams.
  
v1.5
- Dokumentacija sukurta naudojant Doxygen ir įkelta į repoziciją (HTML formatu).
- Pridėti vienetų testai, naudojant pasirinktą C++ testavimo sistemą (Google Test).


Programos funkciju aprasymas:
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

* Eksperimentine analize lyginant kompiliatoriu optimizavimo lygius pasirinkus 1000000 ir 10000000 duomenu irasu failus:
<img width="1626" alt="Screenshot 2024-11-26 at 22 17 41" src="https://github.com/user-attachments/assets/b24e643c-eb42-4f6e-9dde-5635620a6174">

.exe failo paleidimo instrukcija:
	- isikeliame CMakeLists.txt faila is github
	- atsidarius terminala projekto aplankale, ivedame --cmake CMakeLists.txt
 	- po to, --cmake install .
  	- --cmake build .
   	- sukurta .exe faila galima rasti Debug aplankale

Unit test paleidimo instrukcija:
jei dar neturite Google test, reikia atsisiusti:  
- savo aplankale atsidarykite terminala ir klonuokite sia repozitorija:
	git clone https://github.com/google/googletest.git
- atsisiuskite CMakeLists.txt faila is sio Release
- mkdir build
- cd build
- cmake ..
- cmake --build .
- ctest -C Debug
rezultate pamatysite toki outputa:
 <img width="718" alt="Screenshot 2024-12-21 at 11 35 23" src="https://github.com/user-attachments/assets/3903c990-9c2d-4fd4-8f1c-04843827348d" />



