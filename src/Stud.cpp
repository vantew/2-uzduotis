#include "Mylib.h"
#include "Stud.h"
#include "Zmogus.h"

char* Studentas::deepCopy(const char* source) {
    if (!source) return nullptr;
    char* copy = new char[strlen(source) + 1];
    strcpy(copy, source);
    return copy;
}

// Constructor
Studentas::Studentas() :
      egzamRez(0),
      vidurkis(0.0),
      mediana(0.0),
      galutinis(0.0),
      tarpRez(),
      tarpRezlist(),
      containerChoice(0)
{}

Studentas::~Studentas() {
}

Studentas::Studentas(const Studentas& other)
    : Zmogus(other),
      egzamRez(other.egzamRez),
      vidurkis(other.vidurkis),
      mediana(other.mediana),
      galutinis(other.galutinis),
      containerChoice(other.containerChoice),
      tarpRez(other.tarpRez),
      tarpRezlist(other.tarpRezlist)
{}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        Zmogus::operator=(other);
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

int Studentas::getEgzamRez() const { return egzamRez; }

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



template <>
const vector<int>& Studentas::getTarpRez<vector<int>>() const {
    return tarpRez;
}

template <>
const list<int>& Studentas::getTarpRez<list<int>>() const {
    return tarpRezlist;
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
    os << setw(20) << fixed << left << student.getPavarde()
       << setw(20) << student.getVardas()
       << setw(20) << setprecision(2) << student.getGalutinis();
    return os;
}

istream& operator>>(istream& is, Studentas& Lok) {
    string tempVardas, tempPavarde;
    is >> tempVardas >> tempPavarde;
    Lok.setVardas(tempVardas);
    Lok.setPavarde(tempPavarde);

    vector<int> grades;
    int grade;
    cout << "Keep entering grades, when done, type 0." << endl;
    while (is >> grade) {
        if (grade == 0) {
            break;
        }
        grades.push_back(grade);
    }

    if (!grades.empty()) {
        Lok.setEgzamRez(grades.back());
        grades.pop_back();
        Lok.setTarpRez(grades);

        double galutinis = (accumulate(grades.begin(), grades.end(), 0.0) + Lok.getEgzamRez()) / (grades.size() + 1);
        Lok.setGalutinis(galutinis);
    }

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
    if (arRandom == 0)
        cin >> Lok;
    else {
        string vardas, pavarde;
        cin >> vardas >> pavarde;
        Lok.setVardas(vardas);
        Lok.setPavarde(pavarde);

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

        if (vidMed == 1) {
            double galut_med = Lok.calculateMediana(grades);
            cout << setw(20) << setprecision(2) << fixed << galut_med;
        }
    } else {
        const auto& grades = Lok.getTarpRez<list<int>>();
        if (vidMed == 1) {
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
        iss >> vardas >> pavarde;
        Lok.setVardas(vardas);
        Lok.setPavarde(pavarde);

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

    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;
        iss >> Lok;
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
        fwProtingi << student << endl;
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
        fwKvaili << student << endl;
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

    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;
        iss >> Lok;
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
        fwProtingi << student << endl;
    }
    fwProtingi.close();
    cout << "'Kietakai' students file generation: " << e.elapsed() << endl;

    Timer f;
    ofstream fwKvaili("nuskriaustukai.txt");
    fwKvaili << left << setw(20) << "Surname" << setw(20) << "First Name" << setw(20) << "Average" << endl;
    fwKvaili << string(60, '-') << endl;

    for (const auto &student : kvaili) {
        fwKvaili << student << endl;
    }
    fwKvaili.close();
    cout << "'Nuskriaustukai' students file generation: " << f.elapsed() << "\n" << endl;

    cout << "Total time elapsed (excluding file generation): " << a.elapsed() << "\n" << endl;
}
template void inputScanSort2<vector<Studentas>>(string, int);
template void inputScanSort2<list<Studentas>>(string, int);

template <typename Container>
void inputScanSort3(string failoPav, int rusiavKateg) {
    Timer totalTime;

    string filePath = failoPav + ".txt";
    ifstream inputFile(filePath);
    if (!inputFile) {
        cerr << "Error: Cannot open file " << filePath << endl;
        return;
    }

    Timer readTime;
    Container visiStudentai;
    string line;

    // Skip header line
    getline(inputFile, line);

    // Read student data
    while (getline(inputFile, line)) {
        istringstream iss(line);
        Studentas student;
        iss >> student;
        visiStudentai.push_back(student);
    }
    inputFile.close();
    cout << "File reading time elapsed: " << readTime.elapsed() << endl;

    // Sorting based on criteria
    Timer sortTime;
    auto sortFunction = [rusiavKateg](const Studentas& a, const Studentas& b) {
        switch (rusiavKateg) {
            case 0: return string(a.getVardas()) < string(b.getVardas());
            case 1: return string(a.getPavarde()) < string(b.getPavarde());
            default: return a.getGalutinis() > b.getGalutinis();
        }
    };

    if constexpr (is_same<Container, vector<Studentas>>::value) {
        sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);
    } else {
        visiStudentai.sort(sortFunction);
    }
    cout << "Data sorting time elapsed: " << sortTime.elapsed() << endl;

    // Filtering students into separate containers
    Timer filterTime;
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
        auto it = visiStudentai.begin();
        while (it != visiStudentai.end()) {
            if (it->getGalutinis() < 5.0) {
                kvaili.push_back(*it);
                it = visiStudentai.erase(it);
            } else {
                ++it;
            }
        }
    }

    cout << "Data filtering time elapsed: " << filterTime.elapsed() << endl;

    // Writing "kietakai" students
    Timer writeTime;
    ofstream fwProtingi("kietakai.txt");
    fwProtingi << left << setw(20) << "Surname" << setw(20) << "First Name" << setw(20) << "Average" << endl;
    fwProtingi << string(60, '-') << endl;
    for (const auto& student : visiStudentai) {
        fwProtingi << student << endl;
    }
    fwProtingi.close();
    cout << "'Kietakai' students file generation: " << writeTime.elapsed() << endl;

    // Writing "nuskriaustukai" students
    Timer writeFailTime;
    ofstream fwKvaili("nuskriaustukai.txt");
    fwKvaili << left << setw(20) << "Surname" << setw(20) << "First Name" << setw(20) << "Average" << endl;
    fwKvaili << string(60, '-') << endl;
    for (const auto& student : kvaili) {
        fwKvaili << student << endl;
    }
    fwKvaili.close();
    cout << "'Nuskriaustukai' students file generation: " << writeFailTime.elapsed() << "\n" << endl;

    cout << "Total time elapsed: " << totalTime.elapsed() << "\n" << endl;
}

template void inputScanSort3<vector<Studentas>>(string, int);
template void inputScanSort3<list<Studentas>>(string, int);

