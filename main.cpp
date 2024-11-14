#include "Mylib.h"
#include "Stud.h"


int main(){
    vector<Studentas> studentai;
    Studentas laikinasStud;

    int studSk, vidMed, ivedGener, studGenSk, ndGenSk, ivedSkait, rusiavKateg;
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
        exit(EXIT_FAILURE);
    }

    if (ivedGener == 1){
        cout << "How many students will you be grading?" << endl;
        cin >> studGenSk;
        cout << "How many homework grades for each student?" << endl;
        cin >> ndGenSk;
        generate(studGenSk, ndGenSk);
        exit(EXIT_SUCCESS);

    } else if (ivedGener == 2){
        cout << "Which file would you like to test?" << endl;
       // system("ls *.txt"); // 'dir' windowsam
        cout << "Enter the filename, without '.txt'): " << endl;
        cin >> failoPav;
        cout << "If you'd like to sort by name, type '0', " <<endl;
        cout << "by surname, type '1', " << endl;
        cout << "by average '2'. " << endl;
        cin >> rusiavKateg;
        cout << "File alteration initiated." << "\n" << endl;
        inputScanSort(failoPav, rusiavKateg);
        cout << "File alteration ended." << endl;
        exit(EXIT_SUCCESS);
    }

    cout << "If you want to enter student data manually, type '0'," << endl;
    cout << "If you want to read data from a file, type '1'." << endl;
    cin >> ivedSkait;

    if (ivedSkait == 1){
        inputScan(studentai);

        outputScan(studentai);

        exit(EXIT_SUCCESS);
    }

    cout << "How many students will you be grading?" << endl;
    cin >> studSk;

    for (int i=0; i<studSk; i++){ //ciklas sukamas išorėje funkcijų, priešingai nei inputScan
        inputManual(laikinasStud);
        studentai.push_back(laikinasStud);
        clean(laikinasStud);
    }

    cout << "If you want to see the average, type '0'," << endl;
    cout << "to see the median, type '1'." <<endl;
    cin >> vidMed;

    if (vidMed == 0){
        cout << left << setw(20) << "Pavarde"
                  << setw(20) << "Vardas"
                  << setw(20) << "Average"
                  << endl;
        cout << string(60, '-') << endl;
    } else {
        cout << left << setw(20) << "Pavarde"
                  << setw(20) << "Vardas"
                  << setw(20) << "Median"
                  << endl;
        cout << string(60, '-') << endl;
    }

    for (int i=0; i<studSk; i++){ //ciklas sukamas išorėje funkcijų, priešingai nei inputScan
        outputManual(studentai.at(i), vidMed);
    }

    return 0;
}
