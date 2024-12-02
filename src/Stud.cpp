#include "Mylib.h"
#include "Stud.h"
// Helper function for deep copying a C-string
char* Studentas::deepCopy(const char* source) {
    if (!source) return nullptr;
    char* copy = new char[std::strlen(source) + 1];
    std::strcpy(copy, source);
    return copy;
}

// Default Constructor
Studentas::Studentas()
    : vardas(nullptr), pavarde(nullptr), egzamRez(0), vidurkis(0.0), mediana(0.0), galutinis(0.0), containerChoice(0) {}

// Destructor
Studentas::~Studentas() {
    delete[] vardas;
    delete[] pavarde;
}

// Copy Constructor
Studentas::Studentas(const Studentas& other)
    : vardas(deepCopy(other.vardas)), pavarde(deepCopy(other.pavarde)),
      egzamRez(other.egzamRez), vidurkis(other.vidurkis), mediana(other.mediana), galutinis(other.galutinis),
      containerChoice(other.containerChoice), tarpRez(other.tarpRez), tarpRezlist(other.tarpRezlist) {}

// Copy Assignment Operator
Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) { // Check for self-assignment
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

// Getter and Setter for vardas
const char* Studentas::getVardas() const { return vardas; }
void Studentas::setVardas(const std::string& name) {
    delete[] vardas;
    vardas = deepCopy(name.c_str());
}

// Getter and Setter for pavarde
const char* Studentas::getPavarde() const { return pavarde; }
void Studentas::setPavarde(const std::string& surname) {
    delete[] pavarde;
    pavarde = deepCopy(surname.c_str());
}

// Getter and Setter for egzamRez
int Studentas::getEgzamRez() const { return egzamRez; }
void Studentas::setEgzamRez(int egzaminas) { egzamRez = egzaminas; }

// Getter and Setter for galutinis
double Studentas::getGalutinis() const { return galutinis; }
void Studentas::setGalutinis(double finalGrade) { galutinis = finalGrade; }

// Getter and Setter for containerChoice
int Studentas::getContainerChoice() const { return containerChoice; }
void Studentas::setContainerChoice(int choice) { containerChoice = choice; }

template <typename Container>
const Container& Studentas::getTarpRez() const {
    if (containerChoice == 0) {
        return tarpRez;  // For std::vector<int>
    } else {
        return tarpRezlist;  // For std::list<int>
    }
}


// Template function for setting tarpRez (vector or list)
template <typename Container>
void Studentas::setTarpRez(const Container& grades) {
    if (containerChoice == 0) {
        tarpRez.assign(grades.begin(), grades.end());
    } else {
        tarpRezlist.assign(grades.begin(), grades.end());
    }
}
// Define the specialized versions of getTarpRez for std::vector<int> and std::list<int>
template <>
const std::vector<int>& Studentas::getTarpRez<std::vector<int>>() const {
    return tarpRez;
}

template <>
const std::list<int>& Studentas::getTarpRez<std::list<int>>() const {
    return tarpRezlist;
}

// Template calculation methods for vector or list
template <typename Container>
double Studentas::calculateVidurkis(const Container& grades) const {
    if (grades.empty()) return 0.0;
    double sum = std::accumulate(grades.begin(), grades.end(), 0.0);
    return sum / grades.size();
}

template <typename Container>
double Studentas::calculateMediana(const Container& grades) const {
    if (grades.empty()) return 0.0;
    Container sortedGrades = grades;
    if constexpr (std::is_same_v<Container, std::vector<int>>) {
        std::sort(sortedGrades.begin(), sortedGrades.end());
    } else if constexpr (std::is_same_v<Container, std::list<int>>) {
        sortedGrades.sort();
    }

    auto it = std::next(sortedGrades.begin(), sortedGrades.size() / 2);
    if (sortedGrades.size() % 2 == 0) {
        auto prevIt = std::prev(it);
        return (*it + *prevIt) / 2.0;
    } else {
        return *it;
    }
}

// Stream Operators
std::ostream& operator<<(std::ostream& os, const Studentas& Lok) {
    os << std::setw(20) << (Lok.vardas ? Lok.vardas : "N/A")
       << std::setw(20) << (Lok.pavarde ? Lok.pavarde : "N/A");
    return os;
}

std::istream& operator>>(std::istream& is, Studentas& Lok) {
    std::string tempVardas, tempPavarde;
    is >> tempVardas;
    Lok.setVardas(tempVardas);
    is >> tempPavarde;
    Lok.setPavarde(tempPavarde);
    return is;
}

template <typename Container>
void inputManual(Studentas &Lok, Container &grades, int containerChoice) {
    int arRandom;
    std::string input;
    bool praeitasBuvoTuscias = false;

    std::cout << "Do you want to generate the next student's grades?\n";
    std::cout << "For no, type '0', for yes, type '1': ";
    std::cin >> arRandom;

    std::cout << "Input student's name and surname: ";
    std::string vardas, pavarde;
    std::cin >> vardas >> pavarde;
    Lok.setVardas(vardas);
    Lok.setPavarde(pavarde);

    if (arRandom == 0) {
        std::cout << "Input student's exam grade: ";
        int grade;
        std::cin >> grade;
        Lok.setEgzamRez(grade);

        std::cout << "Keep entering grades, when you're done, type '0': ";
        while (true) {
            std::getline(std::cin, input);

            if (input.empty()) {
                if (praeitasBuvoTuscias) {
                    break;
                }
                praeitasBuvoTuscias = true;
            } else {
                praeitasBuvoTuscias = false;

                std::stringstream ss(input);
                int skaicius;

                while (ss >> skaicius) {
                    if (skaicius == 0) {
                        break;
                    }
                    grades.push_back(skaicius);  // Insert into the appropriate container
                }
                Lok.setTarpRez(grades);  // Pass container (vector or list) to setTarpRez

                if (skaicius == 0) {
                    break;
                }
            }
        }
    } else {
        // Randomly generate grades
        grades.clear();  // Clear previous grades
        srand(time(0));
        Lok.setEgzamRez(rand() % 10 + 1);

        std::cout << "Generated grades: ";
        for (int i = 0; i < 5; i++) {
            int hwrez = rand() % 10 + 1;
            grades.push_back(hwrez);  // Insert into the appropriate container
            std::cout << hwrez << " ";
        }
        Lok.setTarpRez(grades);  // Pass container to setTarpRez
        std::cout << std::endl;
    }
}
template void inputManual<std::vector<int>>(Studentas &Lok, std::vector<int> &grades, int containerChoice);
template void inputManual<std::list<int>>(Studentas &Lok, std::list<int> &grades, int containerChoice);


template <typename Container>
void inputScan(Container &studentai) {
    std::ifstream fr("studentai_5.txt"); // File input
    std::string eilute;

    getline(fr, eilute); // Skip header

    while (getline(fr, eilute)) {
        std::istringstream iss(eilute);
        Studentas Lok;

        std::string vardas, pavarde;

        // Use the correct container type for 'balai' based on the container type passed in
        if constexpr (std::is_same<Container, std::vector<Studentas>>::value) {
            std::vector<int> balai;  // For vector, use vector for balai
            int balas;
            while (iss >> balas) {
                balai.push_back(balas);
            }

            if (!balai.empty()) {
                Lok.setEgzamRez(balai.back());
                balai.pop_back();
                Lok.setTarpRez(balai);
            }

        } else if constexpr (std::is_same<Container, std::list<Studentas>>::value) {
            std::list<int> balai;  // For list, use list for balai
            int balas;
            while (iss >> balas) {
                balai.push_back(balas);
            }

            if (!balai.empty()) {
                Lok.setEgzamRez(balai.back());
                balai.pop_back();
                Lok.setTarpRez(balai);
            }
        }

        studentai.push_back(Lok);
    }
    fr.close();
}
template void inputScan<std::vector<Studentas>>(std::vector<Studentas>&);
template void inputScan<std::list<Studentas>>(std::list<Studentas>&);

void outputManual(const Studentas& Lok, int vidMed) {
    cout << Lok;

    if (Lok.getContainerChoice() == 0) {
        const auto& grades = Lok.getTarpRez<std::vector<int>>();

        if (vidMed == 0) {
            double galut_vidurkis = std::accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
            cout << std::setw(20) << std::setprecision(2) << std::fixed << galut_vidurkis;
        } else {
            double galut_med = Lok.calculateMediana(grades);
            cout << std::setw(20) << std::setprecision(2) << std::fixed << galut_med;
        }
    } else {
        const auto& grades = Lok.getTarpRez<std::list<int>>();
        if (vidMed == 0) {
            double galut_vidurkis = std::accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
            cout << std::setw(20) << std::setprecision(2) << std::fixed << galut_vidurkis;
        } else {
            double galut_med = Lok.calculateMediana(grades);
            cout << std::setw(20) << std::setprecision(2) << std::fixed << galut_med;
        }
    }

    cout << std::setw(20) << &Lok << std::endl;
}

template <typename Container>
void outputScan(Container &studentai) {
    cout << "If you would like to filter students by name, type '0', " << endl;
    cout << "by surname '1', " << endl;
    cout << "by average '2'." << endl;

    int rusiavKateg;
    cin >> rusiavKateg;

    // Process the students and calculate their final grades
    for (Studentas &stud : studentai) {
        auto visiRez = stud.getTarpRez<std::vector<int>>();
        visiRez.push_back(stud.getEgzamRez()); // Add exam grade to the container

        double galut_med = stud.calculateMediana(visiRez);
        stud.setGalutinis(galut_med);

        double galut_vidurkis = std::accumulate(visiRez.begin(), visiRez.end(), 0.0) / visiRez.size();
        stud.setGalutinis(galut_vidurkis);
    }

    // Sorting function based on the chosen category
    auto sortFunction = [rusiavKateg](const Studentas &a, const Studentas &b) {
        if (rusiavKateg == 0) return a.getVardas() < b.getVardas();
        if (rusiavKateg == 1) return a.getPavarde() < b.getPavarde();
        return a.getGalutinis() < b.getGalutinis();
    };

    // Sort the container
    if constexpr (std::is_same<Container, std::list<Studentas>>::value) {
        // If the container is a list, use the list's sort function
        studentai.sort(sortFunction);
    } else {
        // If the container is a vector, use std::sort
        std::sort(studentai.begin(), studentai.end(), sortFunction);
    }

    ofstream fw("readstudents.txt");

    fw << left
       << setw(20) << "Surname"
       << setw(20) << "Name"
       << setw(20) << "Average"
       << setw(20) << "Median"
       << endl;

    fw << string(80, '-') << endl;

    // Writing the sorted students to the file
    for (const Studentas &stud : studentai) {
        try {
            auto visiRez = stud.getTarpRez<vector<int>>();
            visiRez.push_back(stud.getEgzamRez());  // Add exam grade

            double galut_med = stud.calculateMediana(visiRez);
            double galut_vidurkis = std::accumulate(visiRez.begin(), visiRez.end(), 0.0) / visiRez.size();

            fw << stud
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
template void outputScan<std::vector<Studentas>>(std::vector<Studentas>&);
template void outputScan<std::list<Studentas>>(std::list<Studentas>&);

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
        if (rusiavKateg == 0) return std::string(a.getVardas()) < std::string(b.getVardas());
        if (rusiavKateg == 1) return std::string(a.getPavarde()) < std::string(b.getPavarde());
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

    if constexpr (is_same<Container, vector<Studentas>>::value) {
        Timer c; // sortingo pradzia
        sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);
        cout << "Data sorting time elapsed: " << c.elapsed() << endl;
    } else {
        Timer c;
        visiStudentai.sort(sortFunction);
        cout << "Data sorting time elapsed: " << c.elapsed() << endl; // sortingo pabaiga
    }

    Timer d; // Filtering start
    Container kvaili;

    if constexpr (is_same<Container, vector<Studentas>>::value) {
        auto it = std::remove_if(visiStudentai.begin(), visiStudentai.end(), [&](const auto& student) {
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

    if constexpr (is_same<Container, vector<Studentas>>::value) {
        sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);
    } else {
        visiStudentai.sort(sortFunction);
    }
    cout << "Data sorting time elapsed: " << c.elapsed() << endl;

    Timer d; // Partitioning
    Container kvaili;

    if constexpr (std::is_same<Container, std::vector<Studentas>>::value) {
        // vector
        auto it = std::partition(visiStudentai.begin(), visiStudentai.end(), [](const auto &student) {
            return student.getGalutinis() >= 5.0;
        });

        kvaili.insert(kvaili.end(), it, visiStudentai.end());
        visiStudentai.erase(it, visiStudentai.end());
    } else {
        // list
        auto it = std::partition(visiStudentai.begin(), visiStudentai.end(), [](const auto &student) {
            return student.getGalutinis() >= 5.0;
        });

        kvaili.splice(kvaili.end(), visiStudentai, it, visiStudentai.end());
    }

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

//void Studentas::reset() {
//    vardas.clear();
//    pavarde.clear();
//    tarpRez.clear();
//    egzamRez = 0;
//    vidurkis = 0.0;
//    mediana = 0.0;
//    galutinis = 0.0;
//}
void Studentas::reset() {
    delete[] vardas;
    delete[] pavarde;
    tarpRez.clear();
    tarpRez.clear();
    vardas = nullptr;
    pavarde = nullptr;
    egzamRez = 0;
    vidurkis = 0.0;
    mediana = 0.0;
    galutinis = 0.0;
}
