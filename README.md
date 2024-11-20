CPU: Apple M2
RAM: 8GB
HDD: SSD

v0.1 - Sukurta programa, kuri leidzia ivairiais budais (rankiniu budu ivesti pazymius, sugeneruoti pazymius arba nuskaityti is failo) ivesti studento duomenis bei egzamino pazymi. Rezultatai atspausdinami surusiuoti pagal vardus arba pavardes (pasirinkta naudotojo) bei leidziama pasirinkti ar stebeti mediana ar vidurki.
v0.2 - Atliekama programos veikimo greicio (spartos) analize, kurios metu isskiriami sie veikimo laikai: duomenu nuskaitymas is failu, studentu rusiavimas i dvi kategorijas bei surusiuotu studentu isvedimas i du naujus failus. Studentai spausdinami rusiuojant pagal naudotojo pasirinkta parametra - varda, pavarde, vidurki.
v0.3 - Atliekama programos veikimo greicio (spartos) analize isskiriant v0.2 pateiktus laikus, kurios metu palyginami vector ir list konteineriai.
v1.0 - Atliekama programos veikimo greicio (spartos) analize isskiriant v0.2 pateiktus laikus, kurios metu palyginami vector ir list konteineriai stebint 2 skirtingas studentu skaidymo strategijas (1 strategija skaido is bendro visu studentu konteinerio i du naujus: kietakus (studentai, kuriu vidurkis >= 5), nuskriaustukus (studentai, kuriu vidurkis < 5), 2 strategija bendra visu studentu konteineri isskiria tik i nuskriaustuku ir juos atima is bendro studentu kiekio, viso to rezultatas: visu studentu konteineryje palieka tik studentai, kuriu vidurkis >= 5, o nuskriaustuku konteinery - studentai, kuriu vidurkis < 5). Isskyrus spartesne strategija, sukuriama nauja 3 strategija ir ji yra optimizuojama tam tikrais algoritmais, si kart taikant strategija tik vektoriaus konteineriui. Galiausiai, yra pateikiamas programos .exe failas.

Programos naudojimosi instrukcija:
Pasirenkama, ar norima ivesti duomenis (0), generuoti failus (1), ar testuoti duomenis (2), t.y. atlikti programos veikimo greicio analize.
Pasirinkus (0), naudotojas yra paklaustas ar nori ivesti studentus bei ju pazymius ranka, ar nori juos generuoti, ar nuskaityti is failo. Galiausiai, pateikiamas pasirinkimas stebeti studentu vidurki arba mediana, rusiuojant pagal naudotojo pasirinkta parametra: varda, pavarde, vidurki.
Pasirinkus (1), naudotojas yra paklaustas ar nori sugeneruoti penkis failus su atsitiktiniais studentais ir siais duomenu irasu kiekiais (1000, 10000, 100000, 1000000, 10000000), ar savarankiskai ivesti norima duomenu irasu kieki. Rezultatas: sugeneruoti failai su atsitiktiniais studentais ir pazymiais tam tikru ivestu duomenu irasu kiekiu.
Pasirinkus (2) yra atliekama programos veikimo greicio (spartos) analize, kurios metu reikia pasirinkti su kuriuo konteineriu atlikti spartos analize ir ivesti testavimo failo pavadinima.
