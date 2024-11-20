#include "Mylib.h"
#include "Stud.h"

double mediana(const vector<int>& v) { // Accept a const reference
    vector<int> temp = v;             // Create a local copy
    size_t n = temp.size();
    sort(temp.begin(), temp.end());   // Sort the local copy
    if (n % 2 == 0) {
        return (temp[n/2 - 1] + temp[n/2]) / 2.0;
    } else {
        return temp[n/2];
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
    cin >> Lok.vardas >> Lok.pavarde;

    if (arRandom == 0) {
        cout << "Input student's exam grade: " << endl;
        cin >> Lok.egzamRez;
        cout << "Keep entering grades, when you're done, type '0': " << endl;

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
                    Lok.tarpRez.push_back(skaicius);
                }
                if (skaicius == 0) {
                    break;
                }
            }
        }
    } else {
        srand(time(0));
        Lok.egzamRez = rand() % 10 + 1;
        cout << "Generated grades for " << Lok.vardas << " " << Lok.pavarde << ": ";
        for (int i = 0; i < 5; i++) { // kiek balu norim kad sugeneruotu (dbr 5)
            int hwrez = rand() % 10 + 1;
            Lok.tarpRez.push_back(hwrez);
            cout << hwrez << " ";
        }
        cout << endl;
    }
}

void inputScan(vector<Studentas> &studentai) {

    ifstream fr("studentai10000.txt"); // is kur nuskaitomas failas
    string eilute;

    getline(fr, eilute);

    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;

        iss >> Lok.pavarde >> Lok.vardas;

        int balas;
        while (iss >> balas) {
            Lok.balai.push_back(balas);
        }

        if (!Lok.balai.empty()) {
            Lok.egzamRez = Lok.balai.back();
            Lok.balai.pop_back();
            Lok.tarpRez = Lok.balai;
        }

        studentai.push_back(Lok);
    }

    fr.close();
}

void outputManual(const Studentas& Lok, int vidMed) {
    if (vidMed == 0) {
        double galut_vidurkis = (accumulate(Lok.tarpRez.begin(), Lok.tarpRez.end(), 0.0) / Lok.tarpRez.size());

        cout << left << setw(20) << Lok.pavarde
             << setw(20) << Lok.vardas
             << setw(20) << setprecision(2) << fixed << galut_vidurkis
             << setw(20) << &Lok << endl; // Print the memory address
    } else {
        double galut_med = mediana(Lok.tarpRez);

        cout << left << setw(20) << Lok.pavarde
             << setw(20) << Lok.vardas
             << setw(20) << setprecision(2) << fixed << galut_med
             << setw(20) << &Lok << endl; // Print the memory address
    }
}

void outputScan(vector<Studentas> &studentai) {
    cout << "If you would like to filter students by name, type '0', " << endl;
    cout << "by surname '1', " << endl;
    cout << "by average '2'." << endl;

    int rusiavKateg;
    cin >> rusiavKateg;

    for (Studentas &stud : studentai) {
        if (stud.tarpRez.empty() || stud.tarpRez.size() == 1) {
            throw runtime_error("Not enough grades for student " + stud.vardas + " " + stud.pavarde + ".");
        }

        vector<int> visiRez = stud.tarpRez;
        visiRez.push_back(stud.egzamRez);
        double galut_med = mediana(visiRez);
        double galut_vidurkis = accumulate(visiRez.begin(), visiRez.end(), 0.0) / visiRez.size();

        stud.galutinis = galut_vidurkis;
    }

    auto sortFunction = [rusiavKateg](const Studentas &a, const Studentas &b) {
        if (rusiavKateg == 0) return a.vardas < b.vardas;  // Sort by name
        if (rusiavKateg == 1) return a.pavarde < b.pavarde;  // Sort by surname
        return a.galutinis < b.galutinis;  // Sort by average grade (asc)
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
            vector<int> visiRez = stud.tarpRez;
            visiRez.push_back(stud.egzamRez);
            double galut_med = mediana(visiRez);
            double galut_vidurkis = accumulate(visiRez.begin(), visiRez.end(), 0.0) / visiRez.size();

            fw << left << setw(20) << stud.pavarde
               << setw(20) << stud.vardas
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
    Timer a; // total time

    Timer b; // Start file reading

    failoPav = failoPav + ".txt";
    ifstream fr(failoPav);
    string eilute;

    getline(fr, eilute);  // Skipping header line

    Container visiStudentai;

    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;

        iss >> Lok.pavarde >> Lok.vardas;

        int balas;
        while (iss >> balas) {
            Lok.balai.push_back(balas);
        }

        if (!Lok.balai.empty()) {
            Lok.egzamRez = Lok.balai.back();
            Lok.balai.pop_back();
            Lok.tarpRez = Lok.balai;
        }

        double galut_vidurkis = (accumulate(Lok.tarpRez.begin(), Lok.tarpRez.end(), 0.0) + Lok.egzamRez) / (Lok.tarpRez.size() + 1);
        Lok.galutinis = galut_vidurkis;

        visiStudentai.push_back(Lok);
    }
    fr.close();

    cout << "File reading time elapsed: " << b.elapsed() << endl; // file readingo pabaiga

    auto sortFunction = [rusiavKateg](const Studentas &a, const Studentas &b) {
        if (rusiavKateg == 0) return a.vardas < b.vardas;
        if (rusiavKateg == 1) return a.pavarde < b.pavarde;
        return a.galutinis > b.galutinis;
    };

    if constexpr (std::is_same<Container, std::vector<Studentas>>::value) {
        Timer c; // sortingo pradzia
        sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);
        cout << "Data sorting time elapsed: " << c.elapsed() << endl;
    } else {
        // Convert list to vector for sorting, then back
        Timer c;
        vector<Studentas> sortedList(visiStudentai.begin(), visiStudentai.end());
        sort(sortedList.begin(), sortedList.end(), sortFunction);
        visiStudentai.assign(sortedList.begin(), sortedList.end());
        cout << "Data sorting time elapsed: " << c.elapsed() << endl; // sortingo pabaiga
    }


    Timer d; // filteringo pradzia

    Container protingi, kvaili;

    for (const auto &student : visiStudentai) {
        if (student.galutinis >= 5.0) {
            protingi.push_back(student);
        } else {
            kvaili.push_back(student);
        }
    }
    visiStudentai.clear();

    cout << "Data filtering time elapsed: " << d.elapsed() << endl; // filteringo pabaiga

    Timer e; // spausdinimo i faila pradzia "kietakai"

    string failasProtingi = "kietakai.txt";
    ofstream fwProtingi(failasProtingi);

    fwProtingi << left
               << setw(20) << "Surname"
               << setw(20) << "First Name"
               << setw(20) << "Average"
               << endl;

    fwProtingi << string(60, '-') << endl;

    for (const auto &student : protingi) {
        fwProtingi << left << setw(20) << student.pavarde << setw(20) << student.vardas
                   << setw(20) << setprecision(2) << fixed << student.galutinis << endl;
    }

    fwProtingi.close();
    protingi.clear();

    cout << "'Kietakai' students file generation: " << e.elapsed() << endl; // spausdinimo i faila pabaiga "kietakai"

    Timer f; // spausdinimo i faila "nuskriaustukai" pradzia

    string failasKvaili = "nuskriaustukai.txt";
    ofstream fwKvaili(failasKvaili);

    fwKvaili << left
             << setw(20) << "Surname"
             << setw(20) << "First Name"
             << setw(20) << "Average"
             << endl;

    fwKvaili << string(60, '-') << endl;

    for (const auto &student : kvaili) {
        fwKvaili << left << setw(20) << student.pavarde << setw(20) << student.vardas
                 << setw(20) << setprecision(2) << fixed << student.galutinis << endl;
    }

    fwKvaili.close();
    kvaili.clear();

    cout << "'Nuskriaustukai' students file generation: " << f.elapsed() << "\n" << endl; // spausdinimo i faila "nuskriaustukai" pabaiga

    cout << "Total time elapsed (excluding file generation): " << a.elapsed() << "\n" << endl; // bendro laiko end
}
template void inputScanSort1<std::vector<Studentas>>(std::string, int);
template void inputScanSort1<std::list<Studentas>>(std::string, int);

template <typename Container>
void inputScanSort2(string failoPav, int rusiavKateg) {
    Timer a; // total time

    Timer b; // Start file reading

    failoPav = failoPav + ".txt";
    ifstream fr(failoPav);
    string eilute;

    getline(fr, eilute);  // Skipping header line

    Container visiStudentai;

    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;

        iss >> Lok.pavarde >> Lok.vardas;

        int balas;
        while (iss >> balas) {
            Lok.balai.push_back(balas);
        }

        if (!Lok.balai.empty()) {
            Lok.egzamRez = Lok.balai.back();
            Lok.balai.pop_back();
            Lok.tarpRez = Lok.balai;
        }

        double galut_vidurkis = (accumulate(Lok.tarpRez.begin(), Lok.tarpRez.end(), 0.0) + Lok.egzamRez) / (Lok.tarpRez.size() + 1);
        Lok.galutinis = galut_vidurkis;

        visiStudentai.push_back(Lok);
    }
    fr.close();

    cout << "File reading time elapsed: " << b.elapsed() << endl; // file readingo pabaiga

    auto sortFunction = [rusiavKateg](const Studentas &a, const Studentas &b) {
        if (rusiavKateg == 0) return a.vardas < b.vardas;
        if (rusiavKateg == 1) return a.pavarde < b.pavarde;
        return a.galutinis > b.galutinis;
    };

    if constexpr (std::is_same<Container, std::vector<Studentas>>::value) {
        Timer c; // sortingo pradzia
        sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);
        cout << "Data sorting time elapsed: " << c.elapsed() << endl;
    } else {
        // Convert list to vector for sorting, then back
        Timer c;
        vector<Studentas> sortedList(visiStudentai.begin(), visiStudentai.end());
        sort(sortedList.begin(), sortedList.end(), sortFunction);
        visiStudentai.assign(sortedList.begin(), sortedList.end());
        cout << "Data sorting time elapsed: " << c.elapsed() << endl; // sortingo pabaiga
    }


    Timer d; // filteringo pradzia

    Container kvaili;

    auto it = std::remove_if(visiStudentai.begin(), visiStudentai.end(), [&](const auto& student) {
        if (student.galutinis < 5.0) {
            kvaili.push_back(student);
            return true; // Mark for removal from visiStudentai
        }
        return false; // Keep in visiStudentai
    });

    cout << "Data filtering time elapsed: " << d.elapsed() << endl; // filteringo pabaiga

    Timer e; // spausdinimo i faila pradzia "kietakai"

    string failasProtingi = "kietakai.txt";
    ofstream fwProtingi(failasProtingi);

    fwProtingi << left
               << setw(20) << "Surname"
               << setw(20) << "First Name"
               << setw(20) << "Average"
               << endl;

    fwProtingi << string(60, '-') << endl;

    for (const auto &student : visiStudentai) {
        fwProtingi << left << setw(20) << student.pavarde << setw(20) << student.vardas
                   << setw(20) << setprecision(2) << fixed << student.galutinis << endl;
    }

    fwProtingi.close();
    visiStudentai.clear();

    cout << "'Kietakai' students file generation: " << e.elapsed() << endl; // spausdinimo i faila pabaiga "kietakai"

    Timer f; // spausdinimo i faila "nuskriaustukai" pradzia

    string failasKvaili = "nuskriaustukai.txt";
    ofstream fwKvaili(failasKvaili);

    fwKvaili << left
             << setw(20) << "Surname"
             << setw(20) << "First Name"
             << setw(20) << "Average"
             << endl;

    fwKvaili << string(60, '-') << endl;

    for (const auto &student : kvaili) {
        fwKvaili << left << setw(20) << student.pavarde << setw(20) << student.vardas
                 << setw(20) << setprecision(2) << fixed << student.galutinis << endl;
    }

    fwKvaili.close();
    kvaili.clear();

    cout << "'Nuskriaustukai' students file generation: " << f.elapsed() << "\n" << endl; // spausdinimo i faila "nuskriaustukai" pabaiga

    cout << "Total time elapsed (excluding file generation): " << a.elapsed() << "\n" << endl; // bendro laiko end
}
template void inputScanSort2<std::vector<Studentas>>(std::string, int);
template void inputScanSort2<std::list<Studentas>>(std::string, int);

template <typename Container>
void inputScanSort3(string failoPav, int rusiavKateg) {
    Timer a; // Total time

    Timer b; // File reading start

    failoPav = failoPav + ".txt";
    ifstream fr(failoPav);
    string eilute;

    getline(fr, eilute); // Skip header line

    Container visiStudentai;

    while (getline(fr, eilute)) {
        istringstream iss(eilute);
        Studentas Lok;

        iss >> Lok.pavarde >> Lok.vardas;

        int balas;
        while (iss >> balas) {
            Lok.balai.push_back(balas);
        }

        if (!Lok.balai.empty()) {
            Lok.egzamRez = Lok.balai.back();
            Lok.balai.pop_back();
            Lok.tarpRez = Lok.balai;
        }

        Lok.galutinis = (std::accumulate(Lok.tarpRez.begin(), Lok.tarpRez.end(), 0.0) + Lok.egzamRez) / (Lok.tarpRez.size() + 1);
        visiStudentai.push_back(Lok);
    }
    fr.close();

    cout << "File reading time elapsed: " << b.elapsed() << endl;

    Timer c; // Sorting start
    auto sortFunction = [rusiavKateg](const Studentas &a, const Studentas &b) {
        if (rusiavKateg == 0) return a.vardas < b.vardas;
        if (rusiavKateg == 1) return a.pavarde < b.pavarde;
        return a.galutinis > b.galutinis;
    };

    if constexpr (std::is_same<Container, std::vector<Studentas>>::value) {
        std::sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);
    } else {
        std::vector<Studentas> sortedList(visiStudentai.begin(), visiStudentai.end());
        std::sort(sortedList.begin(), sortedList.end(), sortFunction);
        visiStudentai.assign(sortedList.begin(), sortedList.end());
    }
    cout << "Data sorting time elapsed: " << c.elapsed() << endl;

    Timer d; // Filtering start
    Container kvaili;

    auto it = std::partition(visiStudentai.begin(), visiStudentai.end(), [](const auto &student) { // PARTITION
        return student.galutinis >= 5.0;
    });

    kvaili.insert(kvaili.end(), it, visiStudentai.end()); //INSERT
    visiStudentai.erase(it, visiStudentai.end()); // ERASE

    cout << "Data filtering time elapsed: " << d.elapsed() << endl;

    Timer e; // File writing start for "kietakai"
    auto writeToFile = [](const string &filename, const auto &container) { // LAMBDA FUNKCIJA
        ofstream file(filename);
        file << left
             << setw(20) << "Surname"
             << setw(20) << "First Name"
             << setw(20) << "Average"
             << endl
             << string(60, '-') << endl; //

        std::for_each(container.begin(), container.end(), [&file](const auto &student) { // FOR_EACH
            file << left << setw(20) << student.pavarde
                 << setw(20) << student.vardas
                 << setw(20) << std::setprecision(2) << std::fixed << student.galutinis
                 << endl;
        });

        file.close();
    };

    writeToFile("kietakai.txt", visiStudentai);
    cout << "'Kietakai' students file generation: " << e.elapsed() << endl;

    Timer f; // File writing start for "nuskriaustukai"
    writeToFile("nuskriaustukai.txt", kvaili);
    cout << "'Nuskriaustukai' students file generation: " << f.elapsed() << "\n" << endl;

    cout << "Total time elapsed (excluding file generation): " << a.elapsed() << "\n" << endl;
}
template void inputScanSort3<std::vector<Studentas>>(std::string, int);
template void inputScanSort3<std::list<Studentas>>(std::string, int);


void clean(Studentas &Lok){
    Lok.vardas.clear();
    Lok.pavarde.clear();
    Lok.tarpRez.clear();
    Lok.balai.clear();
}
