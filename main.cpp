#include "Mylib.h"
#include "Stud.h"

int main() {
    vector<Stud> Vec1;
    Stud Temp;

    cout << "How many students?" << endl;
    int n;
    cin >> n;

    cout << "Do you know the number of homework assignments per student? (y/n):" << endl;
    char hw;
    cin >> hw;
    if (hw == 'y' || hw == 'Y') {
        cout << "Enter the number of assignments: " <<endl;
        int hwCount;
        cin >> hwCount;

        cout << "Input student's data" << endl;
        for (int i = 0; i < n; i++) {
            input(Temp, hwCount);
            Vec1.push_back(Temp);
            clean(Temp);
        }
    }
    else if (hw == 'n' || hw == 'N') {
        cout << "Input student's data" << endl;
        for (int i = 0; i < n; i++) {
            inputgrades(Temp);
            Vec1.push_back(Temp);
            clean(Temp);
        }
    }

int option;

do {
    cout << "Choose option: 1 to view average, 2 to view median: " <<endl;
    cin >> option;

    if (option == 1) {
        printHeaderavg();
        for (Stud student : Vec1) {
            outputavg(student);
        }

        cout << "Do you want to view the Median as well? (y/n): " <<endl;;
        char viewMedian;
        cin >> viewMedian;

        if (viewMedian == 'y' || viewMedian == 'Y') {
            printHeadermed();
            for (Stud student : Vec1) {
                outputmed(student);
            }
        }
    }

    else if (option == 2) {
        printHeadermed();
        for (Stud student : Vec1) {
            outputmed(student);
        }

        cout << "Do you want to view the Average as well? (y/n): ";
        char viewAverage;
        cin >> viewAverage;

        if (viewAverage == 'y' || viewAverage == 'Y') {
            printHeaderavg();
            for (Stud student : Vec1) {
                outputavg(student);
            }
        }
    }
    else {
        cout << "Invalid option! Please try again." << endl;
    }

} while (option != 1 && option != 2); // Continue looping until a valid option is chosen

    system("pause");
}
