#include "Mylib.h"
#include "Stud.h"

double mediana(vector<int> &v){
    size_t n = v.size();
    sort(v.begin(), v.end());
    if (n % 2 == 0) {
        return (v[n/2 - 1] + v[n/2]) / 2.0;
    } else {
        return v[n/2];
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
        for (int i = 0; i < 5; i++) {
            int hwrez = rand() % 10 + 1;
            Lok.tarpRez.push_back(hwrez);
            cout << hwrez << " ";
        }
    }
}

void inputScan(vector<Studentas> &studentai) {

    ifstream fr("studentai10000.txt");
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


void outputManual(Studentas Lok, int vidMed){

    if(vidMed == 0){
        double galut_vidurkis = (accumulate(Lok.tarpRez.begin(), Lok.tarpRez.end(), 0.0)/Lok.tarpRez.size());

        cout << left << setw(20) << Lok.pavarde
        << setw(20) << Lok.vardas << setw(20)<< setprecision(2) << fixed <<
        galut_vidurkis << endl;
    } else {
        double galut_med = (mediana(Lok.tarpRez));

        cout << left << setw(20) << Lok.pavarde
        << setw(20) << Lok.vardas << setw(20) << setprecision(2) << fixed <<
        galut_med << endl;
    }

}

void outputScan(vector<Studentas> &studentai) {
    // Prompt user for sorting criteria
    cout << "If you would like to filter students by name, type '0', " << endl;
    cout << "by surname '1', " << endl;
    cout << "by average '2'." << endl;

    int rusiavKateg;
    cin >> rusiavKateg;

    // Calculate the final grade (galutinis) for each student before sorting
    for (Studentas &stud : studentai) {
        if (stud.tarpRez.empty() || stud.tarpRez.size() == 1) {
            throw runtime_error("Not enough grades for student " + stud.vardas + " " + stud.pavarde + ".");
        }

        vector<int> visiRez = stud.tarpRez;
        visiRez.push_back(stud.egzamRez);
        double galut_med = mediana(visiRez);
        double galut_vidurkis = accumulate(visiRez.begin(), visiRez.end(), 0.0) / visiRez.size();

        stud.galutinis = galut_vidurkis; // Assign the calculated final average to galutinis
        // You can also assign the median if needed
    }

    // Define sorting lambda based on the chosen criteria
    auto sortFunction = [rusiavKateg](const Studentas &a, const Studentas &b) {
        if (rusiavKateg == 0) return a.vardas < b.vardas;  // Sort by name
        if (rusiavKateg == 1) return a.pavarde < b.pavarde;  // Sort by surname
        return a.galutinis < b.galutinis;  // Sort by average grade (descending)
    };

    // Sort the students using the chosen function
    sort(studentai.begin(), studentai.end(), sortFunction);

    // Output to file
    ofstream fw("readstudents.txt");

    fw << left
       << setw(20) << "Surname"
       << setw(20) << "Name"
       << setw(20) << "Average"
       << setw(20) << "Median"
       << endl;

    fw << string(80, '-') << endl;

    // Loop through sorted students and output their details
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


void clean(Studentas &Lok){
    Lok.vardas.clear();
    Lok.pavarde.clear();
    Lok.tarpRez.clear();
    Lok.balai.clear();
}
