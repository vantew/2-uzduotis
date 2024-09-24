#include "Mylib.h"
#include "Stud.h"

int main() {
    vector<Stud> Vec1;
    Stud Temp;

    cout << "How many students?" << endl;
    int n;
    cin >> n;

    char hw;

while (true) {
        cout << "Do you know the number of homework assignments per student? (y/n):" << endl;
        cin >> hw;

        if (hw == 'y' || hw == 'Y') {
            cout << "Enter the number of assignments: " << endl;
            int hwCount;
            cin >> hwCount;

            cout << "Do you want to generate random grades? (y/n): " <<endl;
            char random;
            cin >> random;

            if (random == 'y' || random == 'Y') {
                for (int i = 0; i < n; i++) {
                    randomgrades(Temp, hwCount); // Generate random grades
                    Vec1.push_back(Temp); // Store in vector
                    clean(Temp); // Clean the temporary structure
                }
            break; // Exit the while loop after processing random grades
            }
            else {
                for (int i = 0; i < n; i++) {
                    input(Temp, hwCount);
                    Vec1.push_back(Temp);
                    clean(Temp);
                }
            break; // Exit the loop after processing homework data
            }
        }
        else if (hw == 'n' || hw == 'N') {
            for (int i = 0; i < n; i++) {
                inputgrades(Temp);
                Vec1.push_back(Temp);
                clean(Temp);
            }
            break; // Exit the loop after processing student data
        }
        else {}
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

}
while (option != 1 && option != 2); // Continue looping until a valid option is chosen

system("pause");
}
