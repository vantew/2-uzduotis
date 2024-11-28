#include "Mylib.h"
#include "Stud.h"

void generate(int studGenSk, int ndGenSk, int containerChoice) {
    cout << "File generation initiated" << endl;

    string failoPav = "studentai_" + to_string(studGenSk) + ".txt";
    ofstream fw(failoPav);

    studGenSk += 1;
    ndGenSk += 1;

    Timer t;

    fw << left << setw(15) << "Pavarde" << setw(15) << "Vardas";

    for (int i = 1; i < ndGenSk; i++) {
        fw << "ND" << setw(2) << left << i << " ";
    }

    fw << setw(10) << "Egzaminas" << endl;

    srand(time(0));

    for (int i = 1; i < studGenSk; i++) {
        fw << left << setw(15) << ("Pavarde" + to_string(i))
           << setw(15) << ("Vardas" + to_string(i));

        if (containerChoice == '0') {
            vector<int> grades(ndGenSk - 1);
            for (int j = 0; j < ndGenSk - 1; j++) {
                grades[j] = rand() % 10 + 1;
                fw << setw(5) << grades[j];
            }
        } else {
            list<int> grades;
            for (int j = 0; j < ndGenSk - 1; j++) {
                int grade = rand() % 10 + 1;
                grades.push_back(grade);
                fw << setw(5) << grade;
            }
        }

        fw << setw(10) << rand() % 10 + 1 << endl;
    }

    fw.close();

    cout << to_string(studGenSk - 1) + " student file generated in: " << t.elapsed() << " seconds" << endl;
    cout << "File generation end" << endl;
}
