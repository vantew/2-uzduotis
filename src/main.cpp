#include "Mylib.h"
#include "Stud.h"

int main(){
    vector<Studentas> studentai;
    list<Studentas> studentailist;
    Studentas laikinasStud;

    int studSk, vidMed, ivedGener, studGenSk, ndGenSk, ivedSkait, rusiavKateg, failgen, strateg;
    string failoPav;

    try{
        cout << "If you want to enter data, type '0'," << endl;
        cout << "If you want to generate data, type '1'," << endl;
        cout << "If you want to test data, type '2'." << endl;
        cin >> ivedGener;

        if (!cin){
            throw runtime_error("Enter a given number!");
        }
    }
    catch (const exception& e) {
        cerr << "ERROR:" << e.what() << endl;
        system("pause");
        exit(EXIT_FAILURE);
    }

    int containerChoice;
    cout << "Choose container: '0' for vector, '1' for list: ";
    cin >> containerChoice;

    if (ivedGener == 1){
        cout << "5 Files generation: '1' for yes, '0' for no." << endl;
        cin >> failgen;
        if (failgen == 1) {
            cout << "How many homework grades for each student?" << endl;
            cin >> ndGenSk;
            generate(1000, ndGenSk, containerChoice);
            generate(10000, ndGenSk, containerChoice);
            generate(100000, ndGenSk, containerChoice);
            generate(1000000, ndGenSk, containerChoice);
            generate(10000000, ndGenSk, containerChoice);
            system("pause");
            exit(EXIT_SUCCESS);
        }

        cout << "How many students will you be grading?" << endl;
        cin >> studGenSk;
        cout << "How many homework grades for each student?" << endl;
        cin >> ndGenSk;

        generate(studGenSk, ndGenSk, containerChoice);
        system("pause");
        exit(EXIT_SUCCESS);

    } else if (ivedGener == 2) {
        cout << "Which strategy would you like to use? (1, 2 or 3)" << endl;
        cin >> strateg;
        if (strateg == 1) {
            cout << "Which file would you like to test?" << endl;
            cout << "Enter the filename, without '.txt': " << endl;
            cin >> failoPav;

            cout << "Choose sorting method - by name (0), surname (1), or average (2): " << endl;
            cin >> rusiavKateg;

            if (containerChoice == 0) {
                inputScanSort1<vector<Studentas>>(failoPav, rusiavKateg);
            } else {
                inputScanSort1<list<Studentas>>(failoPav, rusiavKateg);
            }
            system("pause");
            exit(EXIT_SUCCESS);
        } else if (strateg == 2) {
            cout << "Which file would you like to test?" << endl;
            cout << "Enter the filename, without '.txt': " << endl;
            cin >> failoPav;

            cout << "Choose sorting method - by name (0), surname (1), or average (2): " << endl;
            cin >> rusiavKateg;

            if (containerChoice == 0) {
                inputScanSort2<vector<Studentas>>(failoPav, rusiavKateg);
            } else {
                inputScanSort2<list<Studentas>>(failoPav, rusiavKateg);
            }
            system("pause");
            exit(EXIT_SUCCESS);
        } else if (strateg == 3) {
            cout << "Which file would you like to test?" << endl;
            cout << "Enter the filename, without '.txt': " << endl;
            cin >> failoPav;

            cout << "Choose sorting method - by name (0), surname (1), or average (2): " << endl;
            cin >> rusiavKateg;

            if (containerChoice == 0) {
                inputScanSort3<vector<Studentas>>(failoPav, rusiavKateg);
            } else {
                inputScanSort3<list<Studentas>>(failoPav, rusiavKateg);
            }
            system("pause");
            exit(EXIT_SUCCESS);
        }
    }

    cout << "If you want to enter student data manually, type '0'," << endl;
    cout << "If you want to read data from a file, type '1'." << endl;
    cin >> ivedSkait;

    if (ivedSkait == 1){
        inputScan(studentai);

        outputScan(studentai);

        system("pause");
        exit(EXIT_SUCCESS);
    }

    cout << "How many students will you be grading?" << endl;
    cin >> studSk;

    for (int i=0; i<studSk; i++){
        inputManual(laikinasStud);
        studentai.push_back(laikinasStud);
        laikinasStud.clean();
    }

    cout << "If you want to see the average, type '0'," << endl;
    cout << "to see the median, type '1'." <<endl;
    cin >> vidMed;

    if (vidMed == 0){
        cout << left << setw(20) << "Pavarde"
                  << setw(20) << "Vardas"
                  << setw(20) << "Average"
                  << setw(20) << "Memory address"
                  << endl;
        cout << string(80, '-') << endl;
    } else {
        cout << left << setw(20) << "Pavarde"
                  << setw(20) << "Vardas"
                  << setw(20) << "Median"
                  << setw(20) << "Memory address"
                  << endl;
        cout << string(80, '-') << endl;
    }

    for (int i=0; i<studSk; i++){
        outputManual(studentai.at(i), vidMed);
    }
    system("pause");
    return 0;
}
