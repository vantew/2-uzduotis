#include "Mylib.h"
#include "Stud.h"

char* Studentas::deepCopy(const char* source) {
    if (!source) return nullptr;
    char* copy = new char[strlen(source) + 1];
    strcpy(copy, source);
    return copy;
}

// Constructor
Studentas::Studentas()
    : vardas(nullptr), pavarde(nullptr), egzamRez(0), vidurkis(0.0), mediana(0.0), galutinis(0.0), containerChoice(0) {}

// Destructor
Studentas::~Studentas() {
    delete[] vardas;
    delete[] pavarde;
}

Studentas::Studentas(const Studentas& other)
    : vardas(deepCopy(other.vardas)), pavarde(deepCopy(other.pavarde)),
      egzamRez(other.egzamRez), vidurkis(other.vidurkis), mediana(other.mediana), galutinis(other.galutinis),
      containerChoice(other.containerChoice), tarpRez(other.tarpRez), tarpRezlist(other.tarpRezlist) {}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        delete[] vardas;
        delete[] pavarde;

        vardas = deepCopy(other.vardas);
        pavarde = deepCopy(other.pavarde);
        egzamRez = other.egzamRez;
        vidurkis = other.vidurkis;
        mediana = other.mediana;
        galutinis = other.galutinis;
        containerChoice = other.containerChoice;
        tarpRez = other.tarpRez;
        tarpRezlist = other.tarpRezlist;
    }
    return *this;
}

const char* Studentas::getVardas() const { return vardas; }
void Studentas::setVardas(const string& name) {
    delete[] vardas;
    vardas = deepCopy(name.c_str());
}

const char* Studentas::getPavarde() const { return pavarde; }
void Studentas::setPavarde(const string& surname) {
    delete[] pavarde;
    pavarde = deepCopy(surname.c_str());
}

int Studentas::getEgzamRez() const { return egzamRez; }
void Studentas::setEgzamRez(int egzaminas) { egzamRez = egzaminas; }

double Studentas::getGalutinis() const { return galutinis; }
void Studentas::setGalutinis(double finalGrade) { galutinis = finalGrade; }

int Studentas::getContainerChoice() const { return containerChoice; }
void Studentas::setContainerChoice(int choice) { containerChoice = choice; }

template <typename Container>
const Container& Studentas::getTarpRez() const {
    if (containerChoice == 0) {
        return tarpRez;  // vector<int>
    } else {
        return tarpRezlist;  // list<int>
    }
}

template <typename Container>
void Studentas::setTarpRez(const Container& grades) {
    if (containerChoice == 0) {
        tarpRez.assign(grades.begin(), grades.end());
    } else {
        tarpRezlist.assign(grades.begin(), grades.end());
    }
}

template <>
const vector<int>& Studentas::getTarpRez<vector<int>>() const {
    return tarpRez;
}

template <>
const list<int>& Studentas::getTarpRez<list<int>>() const {
    return tarpRezlist;
}

template <typename Container>
double Studentas::calculateVidurkis(const Container& grades) const {
    if (grades.empty()) return 0.0;
    double sum = accumulate(grades.begin(), grades.end(), 0.0);
    return sum / grades.size();
}

template <typename Container>
double Studentas::calculateMediana(const Container& grades) const {
    if (grades.empty()) return 0.0;
    Container sortedGrades = grades;
    if constexpr (is_same_v<Container, vector<int>>) {
        sort(sortedGrades.begin(), sortedGrades.end());
    } else if constexpr (is_same_v<Container, list<int>>) {
        sortedGrades.sort();
    }

    auto it = next(sortedGrades.begin(), sortedGrades.size() / 2);
    if (sortedGrades.size() % 2 == 0) {
        auto prevIt = prev(it);
        return (*it + *prevIt) / 2.0;
    } else {
        return *it;
    }
}

ostream& operator<<(ostream& os, const Studentas& student) {
    os << setw(20) << left << student.getPavarde()
       << setw(20) << student.getVardas();
    return os;
}

istream& operator>>(istream& is, Studentas& Lok) {
    string tempVardas, tempPavarde;
    is >> tempVardas;
    Lok.setVardas(tempVardas);
    is >> tempPavarde;
    Lok.setPavarde(tempPavarde);
    return is;
}

template <typename Container>
void inputManual(Studentas &Lok, Container &grades, int containerChoice) {
    int arRandom;
    string input;
    bool praeitasBuvoTuscias = false;

    cout << "Do you want to generate the next student's grades?\n";
    cout << "For no, type '0', for yes, type '1': ";
    cin >> arRandom;

    cout << "Input student's name and surname: ";
    string vardas, pavarde;
    cin >> Lok;

    if (arRandom == 0) {
        cout << "Input student's exam grade: ";
        int grade;
        cin >> grade;
        Lok.setEgzamRez(grade);

        cout << "Keep entering grades, when you're done, type '0': ";
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
        grades.clear();
        srand(time(0));
        Lok.setEgzamRez(rand() % 10 + 1);

        cout << "Generated grades: ";
        for (int i = 0; i < 5; i++) {
            int hwrez = rand() % 10 + 1;
            grades.push_back(hwrez);
            cout << hwrez << " ";
        }
        Lok.setTarpRez(grades);
        cout << endl;
    }
}
template void inputManual<vector<int>>(Studentas &Lok, vector<int> &grades, int containerChoice);
template void inputManual<list<int>>(Studentas &Lok, list<int> &grades, int containerChoice);

void outputManual(const Studentas& Lok, int vidMed) {
    cout << Lok;

    if (Lok.getContainerChoice() == 0) {
        const auto& grades = Lok.getTarpRez<vector<int>>();

        if (vidMed == 0) {
            double galut_vidurkis = accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
            cout << setw(20) << setprecision(2) << fixed << galut_vidurkis;
        } else {
            double galut_med = Lok.calculateMediana(grades);
            cout << setw(20) << setprecision(2) << fixed << galut_med;
        }
    } else {
        const auto& grades = Lok.getTarpRez<list<int>>();
        if (vidMed == 0) {
            double galut_vidurkis = accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
            cout << setw(20) << setprecision(2) << fixed << galut_vidurkis;
        } else {
            double galut_med = Lok.calculateMediana(grades);
            cout << setw(20) << setprecision(2) << fixed << galut_med;
        }
    }

    cout << setw(20) << &Lok << endl;
}

template <typename Container>
void inoutScan(Container& visiStudentai) {
    string failoPav = "studentai_5.txt";
    ifstream fr(failoPav);

    if (!fr.is_open()) {
        cerr << "Error: Unable to open file " << failoPav << "!" << endl;
        return;
    }

    string eilute;
    getline(fr, eilute); // Skip header line

    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;

        string vardas, pavarde;
        iss >> Lok;

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

    ofstream fw("readstudents.txt");
    if (!fw.is_open()) {
        cerr << "Error: Unable to create file readstudents.txt!" << endl;
        return;
    }

    fw << left
       << setw(20) << "Surname"
       << setw(20) << "First Name"
       << setw(20) << "Average"
       << endl;
    fw << string(60, '-') << endl;

    for (const auto& student : visiStudentai) {
        fw << student
           << setw(20) << setprecision(2) << fixed << student.getGalutinis()
           << endl;
    }

    fw.close();
    cout << "Students have been printed." << endl;
}

template void inoutScan<vector<Studentas>>(vector<Studentas>&);
template void inoutScan<list<Studentas>>(list<Studentas>&);

template <typename Container>
void inputScanSort1(string failoPav, int rusiavKateg) {
    Timer a;
    Timer b;

    failoPav += ".txt";
    ifstream fr(failoPav);
    string eilute;

    getline(fr, eilute);
    Container visiStudentai;

    using GradeContainer = typename conditional<
        is_same<Container, vector<Studentas>>::value,
        vector<int>,
        list<int>>::type;


    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;

        string vardas, pavarde;
        iss >> Lok;

        GradeContainer grades;
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
        if (rusiavKateg == 0) return string(a.getVardas()) < string(b.getVardas());
        if (rusiavKateg == 1) return string(a.getPavarde()) < string(b.getPavarde());
        return a.getGalutinis() > b.getGalutinis();
    };

    if constexpr (is_same<Container, vector<Studentas>>::value) {
        Timer c; // sortingo pradzia
        sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);
        cout << "Data sorting time elapsed: " << c.elapsed() << endl;
    } else {
        Timer c;
        visiStudentai.sort(sortFunction);
        cout << "Data sorting time elapsed: " << c.elapsed() << endl; // sortingo pabaiga
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
        fwProtingi << left << student
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
        fwKvaili << left << student
                 << setw(20) << setprecision(2) << fixed << student.getGalutinis() << endl;
    }
    fwKvaili.close();
    kvaili.clear();

    cout << "'Nuskriaustukai' students file generation: " << f.elapsed() << "\n" << endl;

    cout << "Total time elapsed (excluding file generation): " << a.elapsed() << "\n" << endl;
}
template void inputScanSort1<vector<Studentas>>(string, int);
template void inputScanSort1<list<Studentas>>(string, int);

template <typename Container>
void inputScanSort2(string failoPav, int rusiavKateg) {
    Timer a;
    Timer b;

    failoPav += ".txt";
    ifstream fr(failoPav);
    string eilute;

    getline(fr, eilute);

    Container visiStudentai;

    using GradeContainer = typename conditional<
        is_same<Container, vector<Studentas>>::value,
        vector<int>,
        list<int>>::type;


    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;

        string vardas, pavarde;
        iss >> Lok;

        GradeContainer grades;
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

    if constexpr (is_same<Container, vector<Studentas>>::value) {
        Timer c; // sortingo pradzia
        sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);
        cout << "Data sorting time elapsed: " << c.elapsed() << endl;
    } else {
        Timer c;
        visiStudentai.sort(sortFunction);
        cout << "Data sorting time elapsed: " << c.elapsed() << endl; // sortingo pabaiga
    }

    Timer d;
    Container kvaili;

    if constexpr (is_same<Container, vector<Studentas>>::value) {
        auto it = remove_if(visiStudentai.begin(), visiStudentai.end(), [&](const auto& student) {
            if (student.getGalutinis() < 5.0) {
                kvaili.push_back(student);
                return true;
            }
            return false;
        });
        visiStudentai.erase(it, visiStudentai.end());
    } else if constexpr (is_same<Container, list<Studentas>>::value) {
        visiStudentai.remove_if([&](const auto& student) {
            if (student.getGalutinis() < 5.0) {
                kvaili.push_back(student);
                return true;
            }
            return false;
        });
    }

    cout << "Data filtering time elapsed: " << d.elapsed() << endl;

    Timer e;
    ofstream fwProtingi("kietakai.txt");
    fwProtingi << left << setw(20) << "Surname" << setw(20) << "First Name" << setw(20) << "Average" << endl;
    fwProtingi << string(60, '-') << endl;

    for (const auto &student : visiStudentai) {
        fwProtingi << left << student
                   << setw(20) << setprecision(2) << fixed << student.getGalutinis() << endl;
    }
    fwProtingi.close();
    cout << "'Kietakai' students file generation: " << e.elapsed() << endl;

    Timer f;
    ofstream fwKvaili("nuskriaustukai.txt");
    fwKvaili << left << setw(20) << "Surname" << setw(20) << "First Name" << setw(20) << "Average" << endl;
    fwKvaili << string(60, '-') << endl;

    for (const auto &student : kvaili) {
        fwKvaili << left << student
                 << setw(20) << setprecision(2) << fixed << student.getGalutinis() << endl;
    }
    fwKvaili.close();
    cout << "'Nuskriaustukai' students file generation: " << f.elapsed() << "\n" << endl;

    cout << "Total time elapsed (excluding file generation): " << a.elapsed() << "\n" << endl;
}
template void inputScanSort2<vector<Studentas>>(string, int);
template void inputScanSort2<list<Studentas>>(string, int);

template <typename Container>
void inputScanSort3(string failoPav, int rusiavKateg) {
    Timer a;
    Timer b;

    failoPav += ".txt";
    ifstream fr(failoPav);
    string eilute;

    getline(fr, eilute);

    Container visiStudentai;

    using GradeContainer = typename conditional<
        is_same<Container, vector<Studentas>>::value,
        vector<int>,
        list<int>>::type;


    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;

        string vardas, pavarde;
        iss >> Lok;

        GradeContainer grades;
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

    if constexpr (is_same<Container, vector<Studentas>>::value) {
        sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);
    } else {
        visiStudentai.sort(sortFunction);
    }
    cout << "Data sorting time elapsed: " << c.elapsed() << endl;

    Timer d;
    Container kvaili;

    if constexpr (is_same<Container, vector<Studentas>>::value) {
        // vector
        auto it = partition(visiStudentai.begin(), visiStudentai.end(), [](const auto &student) {
            return student.getGalutinis() >= 5.0;
        });

        kvaili.insert(kvaili.end(), it, visiStudentai.end());
        visiStudentai.erase(it, visiStudentai.end());
    } else {
        // list
        auto it = partition(visiStudentai.begin(), visiStudentai.end(), [](const auto &student) {
            return student.getGalutinis() >= 5.0;
        });

        kvaili.splice(kvaili.end(), visiStudentai, it, visiStudentai.end());
    }

    cout << "Data filtering time elapsed: " << d.elapsed() << endl;

    Timer e;
    ofstream fwProtingi("kietakai.txt");
    fwProtingi << left << setw(20) << "Surname" << setw(20) << "First Name" << setw(20) << "Average" << endl;
    fwProtingi << string(60, '-') << endl;

    for (const auto &student : visiStudentai) {
        fwProtingi << left << student
                   << setw(20) << setprecision(2) << fixed << student.getGalutinis() << endl;
    }
    fwProtingi.close();
    cout << "'Kietakai' students file generation: " << e.elapsed() << endl;

    Timer f;
    ofstream fwKvaili("nuskriaustukai.txt");
    fwKvaili << left << setw(20) << "Surname" << setw(20) << "First Name" << setw(20) << "Average" << endl;
    fwKvaili << string(60, '-') << endl;

    for (const auto &student : kvaili) {
        fwKvaili << left << student
                 << setw(20) << setprecision(2) << fixed << student.getGalutinis() << endl;
    }
    fwKvaili.close();
    cout << "'Nuskriaustukai' students file generation: " << f.elapsed() << "\n" << endl;

    cout << "Total time elapsed (excluding file generation): " << a.elapsed() << "\n" << endl;
}
template void inputScanSort3<vector<Studentas>>(string, int);
template void inputScanSort3<list<Studentas>>(string, int);


void Studentas::reset() {
    delete[] vardas;
    delete[] pavarde;
    tarpRez.clear();
    tarpRezlist.clear();
    vardas = nullptr;
    pavarde = nullptr;
    egzamRez = 0;
    vidurkis = 0.0;
    mediana = 0.0;
    galutinis = 0.0;
}
