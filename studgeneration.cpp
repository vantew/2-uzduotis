#include "Mylib.h"
#include "Stud.h"

class Timer {
  private:
    using hrClock = std::chrono::high_resolution_clock;
    using durationDouble = std::chrono::duration<double>;
    std::chrono::time_point<hrClock> start;
  public:
    Timer() : start{ hrClock::now() } {}
    void reset() {
      start = hrClock::now();
    }
    double elapsed() const {
      return durationDouble (hrClock::now() - start).count();
    }
};

void generate(int studGenSk, int ndGenSk){
    cout << "File generation initiated" << endl;

    string failoPav = "studentai_" + to_string(studGenSk) + ".txt";
    ofstream fw(failoPav);

    studGenSk += 1;
    ndGenSk += 1;

    Timer t;

    fw << left << setw(15) << "Pavarde" << setw(15) << "Vardas";

    for (int i = 1; i < ndGenSk; i++){
        fw << "ND" << setw(2) << left << i << " ";
    }

    fw << setw(10) << "Egzaminas" << endl;

    srand(time(0));

    for (int i = 1; i < studGenSk; i++){
        fw << left << setw(15) << ("Pavarde"+to_string(i))
        << setw(15) << ("Vardas"+to_string(i));

        for (int j = 1; j < ndGenSk; j++){
            fw << setw(5) << rand() % 10 + 1;
        }

        fw << setw(10) << rand() % 10 + 1 << endl;
    }

    fw.close();

    cout << to_string(studGenSk-1) + " student file generated in: " << t.elapsed() << endl;
    cout << "File generation end" << endl;
}

void inputScanSort(string failoPav, int rusiavKateg) {
    Timer a;

    // Failo nuskaitymo pradžia
    Timer b;

    failoPav = failoPav + ".txt";
    ifstream fr(failoPav);
    string eilute;

    getline(fr, eilute);

    vector<Studentas> visiStudentai;
    visiStudentai.reserve(1000000);

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

        double galut_vidurkis = (accumulate(Lok.tarpRez.begin(), Lok.tarpRez.end(), 0.0) + Lok.egzamRez)/(Lok.tarpRez.size() + 1);
        Lok.galutinis = galut_vidurkis;

        visiStudentai.push_back(Lok);
    }
    fr.close();

    // Failo nuskaitymo pabaiga
    cout << "File reading time elapsed: " << b.elapsed() << endl;

    auto sortFunction = [rusiavKateg](const Studentas &a, const Studentas &b) {
        if (rusiavKateg == 0) return a.vardas < b.vardas;
        if (rusiavKateg == 1) return a.pavarde < b.pavarde;
        return a.galutinis > b.galutinis;
    };

    // Visu studentu rikiavimo pradzia
    Timer c;

    sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);

    // Visu studentu rikiavimo  pabaiga
    cout << "Data sorting time elapsed: " << c.elapsed() << endl;

    // Studentu filteringo pradzia
    Timer d;

    vector<Studentas> protingi, kvaili;

    for (const auto &student : visiStudentai) {
        if (student.galutinis >= 5.0) {
            protingi.push_back(student);
        } else {
            kvaili.push_back(student);
        }
    }
    visiStudentai.clear();

    // Studentų dalijimo pabaiga
    cout << "Data filtering time elapsed: " << d.elapsed() << endl;

    // "kietaku" rasymo pradzia
    Timer e;

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

    // "kietaku" studentu rasymo pabaiga
    cout << "'Kietakai' students file generation: " << e.elapsed() << endl;

    // "nuskriaustuku" studentu rasymo pradzia
    Timer f;

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

    // "nuskriaustuku" studentu rasymo pradzia
    cout << "'Nuskriaustukai' students file generation: " << f.elapsed() << "\n" << endl;

    cout << "Total time elapsed (excluding file generation): " << a.elapsed() << "\n" << endl;
}
