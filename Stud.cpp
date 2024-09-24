#include "Stud.h"

void input(Stud &Lok, int hwCount) {
    cout << "Input student's name and surname: " << endl;
    cin >> Lok.name >> Lok.surname;

    double hwSum = 0;  // To calculate homework total sum
    int hw;

    cout << "Enter the homework grades for " << "\033[1;3m" << Lok.name << " " << Lok.surname << "\033[0m: " << endl;
    for (int i = 0; i < hwCount; i++) {
        cin >> hw;
        hwSum += hw;
        Lok.HW.push_back(hw);
          // Add to total homework sum
    }
    cout << "Enter the exam grade: " << endl;
    int m = 1;
    for (int i = 0; i < m; i++) {
        cin >> Lok.exam;
        if ((Lok.exam < 1) || (Lok.exam > 10)) {
            cout << "Invalid number! Try again." <<endl;
            i--;
            }
    }

    Lok.HW.push_back(Lok.exam);
    Lok.med = calculateMedian(Lok.HW);  // Calculate median
    Lok.avg = (hwSum + Lok.exam) / (hwCount + 1);
}

void inputgrades(Stud &Lok) {
    cout << "Input student's name and surname: " << endl;
    cin >> Lok.name >> Lok.surname;

    int hw;
    int hwSum = 0;
    int hwCount = 0;

    cout << "Enter the homework grades for \033[1;3m" << Lok.name << " "
    << Lok.surname << "\033[0m, when you are done, type 0." << endl;
    while (true) {
        cin >> hw;

        if (hw == 0) {
            break;
        }
        else if ((hw < 1) || (hw > 10)) {
            cout << "Invalid number! Try again." <<endl;
            }
            else {
                hwSum += hw;
                hwCount++;
                Lok.HW.push_back(hw);
            }
    }

    cout << "Enter the exam grade: " << endl;
    int m = 1;
    for (int i = 0; i < m; i++) {
        cin >> Lok.exam;
        if ((Lok.exam < 1) || (Lok.exam > 10)) {
            cout << "Invalid number! Try again." <<endl;
            i--;
            }
    }

    Lok.HW.push_back(Lok.exam);
    Lok.med = calculateMedian(Lok.HW);  // Calculate median
    Lok.avg = (hwSum + Lok.exam) / (hwCount + 1);
}

void randomgrades(Stud &Lok, int hwCount) {
    cout << "Input student's name and surname: " << endl;
    cin >> Lok.name >> Lok.surname;

    int hw;
    int hwSum = 0;
    // Seed the random number generator
   // std::srand(static_cast<unsigned int>(std::time(0)));

    for (int i = 0; i < hwCount; i++) {
        int hw = (std::rand() % 10) + 1; // Generate grade between 1 and 10
        Lok.HW.push_back(hw);
        hwSum += hw;
        cout << " a " << hw << " a" <<endl;
    }

    Lok.exam = (std::rand() % 10) + 1; // Generate grade between 1 and 10
    Lok.HW.push_back(Lok.exam);

    Lok.med = calculateMedian(Lok.HW);  // Calculate median
    Lok.avg = (hwSum + Lok.exam) / (hwCount + 1);

}

double calculateMedian(vector<double>& grades) {
    if (grades.empty()) return 0;

    sort(grades.begin(), grades.end());

    size_t size = grades.size();
    if (size % 2 == 0) {
        return (grades[size / 2 - 1] + grades[size / 2]) / 2;
    } else {
        return grades[size / 2];
    }
}

void printHeaderavg() {
    cout << left << setw(12) << "Surname"
         << setw(12) << "Name"
         << setw(8) << "Average" << endl;
    cout << string(12 + 12 + 8, '-') << endl;
}

void printHeadermed() {
    cout << left << setw(12) << "Surname"
         << setw(12) << "Name"
         << setw(8) << "Median" << endl;
    cout << string(12 + 12 + 8, '-') << endl;
}

void outputavg(Stud Lok) {
    cout << left << setw(12) << Lok.surname
         << setw(12) << Lok.name
         << setw(8) << fixed << setprecision(2) << Lok.avg << endl;
}

void outputmed(Stud Lok) {
    cout << left << setw(12) << Lok.surname
         << setw(12) << Lok.name
         << setw(8) << fixed << setprecision(2) << Lok.med << endl;
}

void clean(Stud &Lok) {
    Lok.name.clear();
    Lok.surname.clear();
    Lok.HW.clear();
}
