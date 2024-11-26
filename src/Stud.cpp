#include "Mylib.h"
#include "Stud.h"

void Studentas::copyString(char*& dest, const char* src) {
    if (src) {
        size_t len = std::strlen(src);
        dest = new char[len + 1];
        std::memcpy(dest, src, len);
        dest[len] = '\0';
    } else {
        dest = nullptr;
    }
}

Studentas::Studentas(const char* v, const char* p)
    : vardas(nullptr), pavarde(nullptr), egzamRez(0), vidurkis(0.0), mediana(0.0), galutinis(0.0) {
    copyString(vardas, v);
    copyString(pavarde, p);
}

Studentas::~Studentas() {
    delete[] vardas;
    delete[] pavarde;
}

Studentas::Studentas(const Studentas& other)
    : vardas(nullptr), pavarde(nullptr), tarpRez(other.tarpRez), egzamRez(other.egzamRez),
      vidurkis(other.vidurkis), mediana(other.mediana), galutinis(other.galutinis) {
    copyString(vardas, other.vardas);
    copyString(pavarde, other.pavarde);
}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        Studentas temp(other);
        std::swap(vardas, temp.vardas);
        std::swap(pavarde, temp.pavarde);
        std::swap(tarpRez, temp.tarpRez);
        std::swap(egzamRez, temp.egzamRez);
        std::swap(vidurkis, temp.vidurkis);
        std::swap(mediana, temp.mediana);
        std::swap(galutinis, temp.galutinis);
    }
    return *this;
}

const char* Studentas::getVardas() const {
    return vardas;
}

void Studentas::setVardas(const char* name) {
    delete[] vardas;
    copyString(vardas, name);
}

void Studentas::setVardas(const std::string& name) {
    setVardas(name.c_str());
}

const char* Studentas::getPavarde() const {
    return pavarde;
}

void Studentas::setPavarde(const char* surname) {
    delete[] pavarde;
    copyString(pavarde, surname);
}

void Studentas::setPavarde(const std::string& surname) {
    setPavarde(surname.c_str());
}


const std::vector<int>& Studentas::getTarpRez() const {
    return tarpRez;
}

void Studentas::setTarpRez(const std::vector<int>& grades) {
    tarpRez = grades;
}

int Studentas::getEgzamRez() const {
    return egzamRez;
}

void Studentas::setEgzamRez(int egzaminas) {
    egzamRez = egzaminas;
}

double Studentas::getGalutinis() const {
    return galutinis;
}

void Studentas::setGalutinis(double finalGrade) {
    galutinis = finalGrade;
}

double Studentas::calculateVidurkis() const {
    if (tarpRez.empty()) return 0.0;
    return static_cast<double>(std::accumulate(tarpRez.begin(), tarpRez.end(), 0)) / tarpRez.size();
}

double Studentas::calculateMediana() const {
    if (tarpRez.empty()) return 0.0;
    std::vector<int> sortedGrades = tarpRez;
    std::sort(sortedGrades.begin(), sortedGrades.end());
    size_t size = sortedGrades.size();
    if (size % 2 == 0) {
        return (sortedGrades[size / 2 - 1] + sortedGrades[size / 2]) / 2.0;
    } else {
        return sortedGrades[size / 2];
    }
}

void inputManual(Studentas &Lok){
    int arRandom;
    string input;
    bool praeitasBuvoTuscias = false;

    cout << "Do you want to generate the next student's grades?" <<endl;
    cout << "For no, type '0', for yes, type '1'." << endl;
    cin >> arRandom;

    cout << "Input student's name and surname: " << endl;
    string vardas, pavarde;
    cin >> vardas >> pavarde;
    Lok.setVardas(vardas);
    Lok.setPavarde(pavarde);

    if (arRandom == 0) {
        cout << "Input student's exam grade: " << endl;
        int grade;
        cin >> grade;
        Lok.setEgzamRez(grade);
        cout << "Keep entering grades, when you're done, type '0': " << endl;
        vector<int> grades;

        while (true) {
            getline(cin, input);

            if (input.empty()) {
                if (praeitasBuvoTuscias) {
                    break;
                }
                praeitasBuvoTuscias = true;
            } else {
                praeitasBuvoTuscias = false;

                stringstream ss(input);
                int skaicius;

                while (ss >> skaicius) {
                    if (skaicius == 0) {
                        break;
                    }
                    grades.push_back(skaicius);
                }
                Lok.setTarpRez(grades);
                if (skaicius == 0) {
                    break;
                }
            }
        }
    } else {
        vector<int> grades;
        srand(time(0));
        Lok.setEgzamRez(rand() % 10 + 1);
        cout << "Generated grades: ";
        for (int i = 0; i < 5; i++) { // kiek balu norim kad sugeneruotu (dbr 5)
            int hwrez = rand() % 10 + 1;
            grades.push_back(hwrez);
            cout << hwrez << " ";
        }
        Lok.setTarpRez(grades);
        cout << endl;
    }
}

void inputScan(vector<Studentas> &studentai) {
    ifstream fr("studentai_10000.txt"); // File input
    string eilute;

    getline(fr, eilute); // Skip header

    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;

        string vardas, pavarde;
        vector<int> balai;
        int balas;

        iss >> pavarde >> vardas;
        Lok.setPavarde(pavarde);
        Lok.setVardas(vardas);

        while (iss >> balas) {
            balai.push_back(balas);
        }

        if (!balai.empty()) {
            Lok.setEgzamRez(balai.back());
            balai.pop_back();
            Lok.setTarpRez(balai);
        }

        studentai.push_back(Lok);
    }
    fr.close();
}


void outputManual(const Studentas &Lok, int vidMed) {
    if (vidMed == 0) {
        double galut_vidurkis = accumulate(Lok.getTarpRez().begin(), Lok.getTarpRez().end(), 0.0) / Lok.getTarpRez().size();

        cout << left << setw(20) << Lok.getPavarde()
             << setw(20) << Lok.getVardas()
             << setw(20) << setprecision(2) << fixed << galut_vidurkis << setw(20) << &Lok << endl;
    } else {
        double galut_med = Lok.calculateMediana();

        cout << left << setw(20) << Lok.getPavarde()
             << setw(20) << Lok.getVardas()
             << setw(20) << setprecision(2) << fixed << galut_med << setw(20) << &Lok << endl;
    }
}

void outputScan(vector<Studentas> &studentai) {
    cout << "If you would like to filter students by name, type '0', " << endl;
    cout << "by surname '1', " << endl;
    cout << "by average '2'." << endl;

    int rusiavKateg;
    cin >> rusiavKateg;

    for (Studentas &stud : studentai) {
        vector<int> visiRez = stud.getTarpRez();
        visiRez.push_back(stud.getEgzamRez());

        double galut_med = stud.calculateMediana();
        stud.setGalutinis(galut_med);
        double galut_vidurkis = accumulate(visiRez.begin(), visiRez.end(), 0.0) / visiRez.size();
        stud.setGalutinis(galut_vidurkis);
    }

    auto sortFunction = [rusiavKateg](const Studentas &a, const Studentas &b) {
        if (rusiavKateg == 0) return a.getVardas() < b.getVardas();
        if (rusiavKateg == 1) return a.getPavarde() < b.getPavarde();
        return a.getGalutinis() < b.getGalutinis();
    };

    sort(studentai.begin(), studentai.end(), sortFunction);

    ofstream fw("readstudents.txt");

    fw << left
       << setw(20) << "Surname"
       << setw(20) << "Name"
       << setw(20) << "Average"
       << setw(20) << "Median"
       << endl;

    fw << string(80, '-') << endl;

    for (const Studentas &stud : studentai) {
        try {
        vector<int> visiRez = stud.getTarpRez();
        visiRez.push_back(stud.getEgzamRez());

        double galut_med = stud.calculateMediana();
        double galut_vidurkis = accumulate(visiRez.begin(), visiRez.end(), 0.0) / visiRez.size();

        fw << left << setw(20) << stud.getPavarde()
           << setw(20) << stud.getVardas()
           << setw(20) << setprecision(2) << fixed << galut_vidurkis
           << setw(20) << setprecision(2) << fixed << galut_med
           << endl;
        }
        catch (const exception& e) {
            cerr << "ERROR: " << e.what() << endl;
            exit(EXIT_FAILURE);
        }
    }

    cout << "Chosen file is read and students are sorted." << endl;
    fw.close();
}

template <typename Container>
void inputScanSort1(string failoPav, int rusiavKateg) {
    Timer a; // Total time
    Timer b; // File reading start

    failoPav += ".txt";
    ifstream fr(failoPav);
    string eilute;

    getline(fr, eilute); // Skip header line
    Container visiStudentai;

    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;

        string vardas, pavarde;
        iss >> pavarde >> vardas;
        Lok.setPavarde(pavarde);
        Lok.setVardas(vardas);

        vector<int> grades;
        int balas;
        while (iss >> balas) {
            grades.push_back(balas);
        }

        if (!grades.empty()) {
            Lok.setEgzamRez(grades.back());
            grades.pop_back();
            Lok.setTarpRez(grades);
        }

        Lok.setGalutinis((accumulate(grades.begin(), grades.end(), 0.0) + Lok.getEgzamRez()) / (grades.size() + 1));
        visiStudentai.push_back(Lok);
    }
    fr.close();

    cout << "File reading time elapsed: " << b.elapsed() << endl;

    auto sortFunction = [rusiavKateg](const Studentas &a, const Studentas &b) {
        if (rusiavKateg == 0) return a.getVardas() < b.getVardas();
        if (rusiavKateg == 1) return a.getPavarde() < b.getPavarde();
        return a.getGalutinis() > b.getGalutinis();
    };

    if constexpr (std::is_same<Container, std::vector<Studentas>>::value) {
        Timer c;
        sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);
        cout << "Data sorting time elapsed: " << c.elapsed() << endl;
    } else {
        Timer c;
        vector<Studentas> sortedList(visiStudentai.begin(), visiStudentai.end());
        sort(sortedList.begin(), sortedList.end(), sortFunction);
        visiStudentai.assign(sortedList.begin(), sortedList.end());
        cout << "Data sorting time elapsed: " << c.elapsed() << endl;
    }

    Timer d;
    Container protingi, kvaili;

    for (const auto &student : visiStudentai) {
        if (student.getGalutinis() >= 5.0) {
            protingi.push_back(student);
        } else {
            kvaili.push_back(student);
        }
    }
    visiStudentai.clear();

    cout << "Data filtering time elapsed: " << d.elapsed() << endl;

    Timer e;
    ofstream fwProtingi("kietakai.txt");

    fwProtingi << left
               << setw(20) << "Surname"
               << setw(20) << "First Name"
               << setw(20) << "Average"
               << endl;
    fwProtingi << string(60, '-') << endl;

    for (const auto &student : protingi) {
        fwProtingi << left << setw(20) << student.getPavarde()
                   << setw(20) << student.getVardas()
                   << setw(20) << setprecision(2) << fixed << student.getGalutinis() << endl;
    }
    fwProtingi.close();
    protingi.clear();

    cout << "'Kietakai' students file generation: " << e.elapsed() << endl;

    Timer f;
    ofstream fwKvaili("nuskriaustukai.txt");

    fwKvaili << left
             << setw(20) << "Surname"
             << setw(20) << "First Name"
             << setw(20) << "Average"
             << endl;
    fwKvaili << string(60, '-') << endl;

    for (const auto &student : kvaili) {
        fwKvaili << left << setw(20) << student.getPavarde()
                 << setw(20) << student.getVardas()
                 << setw(20) << setprecision(2) << fixed << student.getGalutinis() << endl;
    }
    fwKvaili.close();
    kvaili.clear();

    cout << "'Nuskriaustukai' students file generation: " << f.elapsed() << "\n" << endl;

    cout << "Total time elapsed (excluding file generation): " << a.elapsed() << "\n" << endl;
}
template void inputScanSort1<std::vector<Studentas>>(std::string, int);
template void inputScanSort1<std::list<Studentas>>(std::string, int);

template <typename Container>
void inputScanSort2(string failoPav, int rusiavKateg) {
    Timer a; // total time
    Timer b; // Start file reading

    failoPav += ".txt";
    ifstream fr(failoPav);
    string eilute;

    getline(fr, eilute); // Skip header line

    Container visiStudentai;

    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;

        string vardas, pavarde;
        iss >> pavarde >> vardas;
        Lok.setPavarde(pavarde);
        Lok.setVardas(vardas);

        vector<int> grades;
        int balas;
        while (iss >> balas) {
            grades.push_back(balas);
        }

        if (!grades.empty()) {
            Lok.setEgzamRez(grades.back());
            grades.pop_back();
            Lok.setTarpRez(grades);
        }

        double galut_vidurkis = (accumulate(grades.begin(), grades.end(), 0.0) + Lok.getEgzamRez()) / (grades.size() + 1);
        Lok.setGalutinis(galut_vidurkis);

        visiStudentai.push_back(Lok);
    }
    fr.close();

    cout << "File reading time elapsed: " << b.elapsed() << endl;

    auto sortFunction = [rusiavKateg](const Studentas &a, const Studentas &b) {
        if (rusiavKateg == 0) return a.getVardas() < b.getVardas();
        if (rusiavKateg == 1) return a.getPavarde() < b.getPavarde();
        return a.getGalutinis() > b.getGalutinis();
    };

    if constexpr (std::is_same<Container, std::vector<Studentas>>::value) {
        Timer c;
        sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);
        cout << "Data sorting time elapsed: " << c.elapsed() << endl;
    } else {
        Timer c;
        vector<Studentas> sortedList(visiStudentai.begin(), visiStudentai.end());
        sort(sortedList.begin(), sortedList.end(), sortFunction);
        visiStudentai.assign(sortedList.begin(), sortedList.end());
        cout << "Data sorting time elapsed: " << c.elapsed() << endl;
    }

    Timer d; // Filtering start
    Container kvaili;

    auto it = remove_if(visiStudentai.begin(), visiStudentai.end(), [&](const Studentas &student) {
        if (student.getGalutinis() < 5.0) {
            kvaili.push_back(student);
            return true;
        }
        return false;
    });
    visiStudentai.erase(it, visiStudentai.end());

    cout << "Data filtering time elapsed: " << d.elapsed() << endl;

    Timer e; // Writing "kietakai"
    ofstream fwProtingi("kietakai.txt");
    fwProtingi << left << setw(20) << "Surname" << setw(20) << "First Name" << setw(20) << "Average" << endl;
    fwProtingi << string(60, '-') << endl;

    for (const auto &student : visiStudentai) {
        fwProtingi << left << setw(20) << student.getPavarde() << setw(20) << student.getVardas()
                   << setw(20) << setprecision(2) << fixed << student.getGalutinis() << endl;
    }
    fwProtingi.close();
    cout << "'Kietakai' students file generation: " << e.elapsed() << endl;

    Timer f; // Writing "nuskriaustukai"
    ofstream fwKvaili("nuskriaustukai.txt");
    fwKvaili << left << setw(20) << "Surname" << setw(20) << "First Name" << setw(20) << "Average" << endl;
    fwKvaili << string(60, '-') << endl;

    for (const auto &student : kvaili) {
        fwKvaili << left << setw(20) << student.getPavarde() << setw(20) << student.getVardas()
                 << setw(20) << setprecision(2) << fixed << student.getGalutinis() << endl;
    }
    fwKvaili.close();
    cout << "'Nuskriaustukai' students file generation: " << f.elapsed() << "\n" << endl;

    cout << "Total time elapsed (excluding file generation): " << a.elapsed() << "\n" << endl;
}
template void inputScanSort2<std::vector<Studentas>>(std::string, int);
template void inputScanSort2<std::list<Studentas>>(std::string, int);

template <typename Container>
void inputScanSort3(string failoPav, int rusiavKateg) {
    Timer a; // Total time
    Timer b; // File reading start

    failoPav += ".txt";
    ifstream fr(failoPav);
    string eilute;

    getline(fr, eilute); // Skip header line

    Container visiStudentai;

    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;

        string vardas, pavarde;
        iss >> pavarde >> vardas;
        Lok.setPavarde(pavarde);
        Lok.setVardas(vardas);

        vector<int> grades;
        int balas;
        while (iss >> balas) {
            grades.push_back(balas);
        }

        if (!grades.empty()) {
            Lok.setEgzamRez(grades.back());
            grades.pop_back();
            Lok.setTarpRez(grades);
        }

        Lok.setGalutinis((accumulate(grades.begin(), grades.end(), 0.0) + Lok.getEgzamRez()) / (grades.size() + 1));
        visiStudentai.push_back(Lok);
    }
    fr.close();

    cout << "File reading time elapsed: " << b.elapsed() << endl;

    Timer c; // Sorting start
    auto sortFunction = [rusiavKateg](const Studentas &a, const Studentas &b) {
        if (rusiavKateg == 0) return a.getVardas() < b.getVardas();
        if (rusiavKateg == 1) return a.getPavarde() < b.getPavarde();
        return a.getGalutinis() > b.getGalutinis();
    };

    if constexpr (std::is_same<Container, std::vector<Studentas>>::value) {
        sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);
    } else {
        vector<Studentas> sortedList(visiStudentai.begin(), visiStudentai.end());
        sort(sortedList.begin(), sortedList.end(), sortFunction);
        visiStudentai.assign(sortedList.begin(), sortedList.end());
    }
    cout << "Data sorting time elapsed: " << c.elapsed() << endl;

    Timer d; // Partitioning
    Container kvaili;
    auto it = partition(visiStudentai.begin(), visiStudentai.end(), [](const Studentas &student) {
        return student.getGalutinis() >= 5.0;
    });
    kvaili.insert(kvaili.end(), it, visiStudentai.end());
    visiStudentai.erase(it, visiStudentai.end());

    cout << "Data filtering time elapsed: " << d.elapsed() << endl;

    Timer e; // Writing "kietakai"
    ofstream fwProtingi("kietakai.txt");
    fwProtingi << left << setw(20) << "Surname" << setw(20) << "First Name" << setw(20) << "Average" << endl;
    fwProtingi << string(60, '-') << endl;

    for (const auto &student : visiStudentai) {
        fwProtingi << left << setw(20) << student.getPavarde() << setw(20) << student.getVardas()
                   << setw(20) << setprecision(2) << fixed << student.getGalutinis() << endl;
    }
    fwProtingi.close();
    cout << "'Kietakai' students file generation: " << e.elapsed() << endl;

    Timer f; // Writing "nuskriaustukai"
    ofstream fwKvaili("nuskriaustukai.txt");
    fwKvaili << left << setw(20) << "Surname" << setw(20) << "First Name" << setw(20) << "Average" << endl;
    fwKvaili << string(60, '-') << endl;

    for (const auto &student : kvaili) {
        fwKvaili << left << setw(20) << student.getPavarde() << setw(20) << student.getVardas()
                 << setw(20) << setprecision(2) << fixed << student.getGalutinis() << endl;
    }
    fwKvaili.close();
    cout << "'Nuskriaustukai' students file generation: " << f.elapsed() << "\n" << endl;

    cout << "Total time elapsed (excluding file generation): " << a.elapsed() << "\n" << endl;
}
template void inputScanSort3<std::vector<Studentas>>(std::string, int);
template void inputScanSort3<std::list<Studentas>>(std::string, int);


void Studentas::clean() {
    delete[] vardas;
    delete[] pavarde;
    vardas = nullptr;
    pavarde = nullptr;
    tarpRez.clear();
    egzamRez = 0;
    vidurkis = 0.0;
    mediana = 0.0;
    galutinis = 0.0;
}
