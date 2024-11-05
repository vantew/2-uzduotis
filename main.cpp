#include "Mylib.h"
#include "Stud.h"

int main() {
    vector<Stud> Vec1;
    list<Stud> List1;
        vector<Stud> below5;
        vector<Stud> above5;
        list<Stud> below5list;
        list<Stud> above5list;

    Stud Temp;

    char fileoption;
    do {
        cout << "Do you want to read student information from a file? (y/n): ";
        cin >> fileoption;

        if (fileoption != 'y' && fileoption != 'Y' && fileoption != 'n' && fileoption != 'N') {
            cout << "Invalid input. Please enter 'y' or 'n'." << endl;
        }

    } while (fileoption != 'y' && fileoption != 'Y' && fileoption != 'n' && fileoption != 'N');

    if (fileoption == 'y' || fileoption == 'Y') {
    try {
        ifstream file("studentai10000.txt");
        if (!file.is_open()) {
            throw runtime_error("Failed to open input file.");
        }

        string line;
        getline(file, line); // read the header

        while (getline(file, line)) { // read the file line by line
            readfile(line, Temp);
            Vec1.push_back(Temp);
            List1.push_back(Temp);
            clean(Temp);
        }


        char filteroption;
        cout << "Enter filter option ('1' to print students whose average is above 5, '2' for below 5, '3' for both): ";
        cin >> filteroption;
        char container;
        cout << "Would you like to view the statistics with vector or list, or both? (v/l/b)" << endl;
        cin >> container;
        cout << endl;

//        vector<Stud> below5;
//        vector<Stud> above5;
//        list<Stud> below5list;
//        list<Stud> above5list;

        if (filteroption == '1') {
            if (container == 'v') {
                filterabove5(Vec1, above5);
                savetofile("above5output.txt", above5);
            }
            else if (container == 'l') {
                filterabove5List(List1, above5list);
                savetofileList("above5output.txt", above5list);
            }
            else if (container == 'b') {
                filterabove5(Vec1, above5);
                savetofile("above5output.txt", above5);

                filterabove5List(List1, above5list);
                savetofileList("above5output.txt", above5list);
            }

        }
        else if (filteroption == '2') {
            if (container == 'v') {
                filterbelow5(Vec1, below5);
                savetofile("below5output.txt", below5);
            }
            else if (container == 'l') {
                filterbelow5List(List1, below5list);
                savetofileList("below5output.txt", below5list);
            }
            else if (container == 'b') {
                filterbelow5(Vec1, below5);
                savetofile("below5output.txt", below5);

                filterbelow5List(List1, below5list);
                savetofileList("below5output.txt", below5list);
            }

        }
        else if (filteroption == '3') {
            if (container == 'v') {
                filterbelow5(Vec1, below5);
                filterabove5(Vec1, above5);
                savetofile("below5output.txt", below5);
                savetofile("above5output.txt", above5);
            }
            else if (container == 'l') {
                filterbelow5List(List1, below5list);
                filterabove5List(List1, above5list);
                savetofileList("below5output.txt", below5list);
                savetofileList("above5output.txt", above5list);
            }
            else if (container == 'b') {
                filterbelow5(Vec1, below5);
                filterabove5(Vec1, above5);
                savetofile("below5output.txt", below5);
                savetofile("above5output.txt", above5);

                filterbelow5List(List1, below5list);
                filterabove5List(List1, above5list);
                savetofileList("below5output.txt", below5list);
                savetofileList("above5output.txt", above5list);
            }

        }

        file.close();

        system("pause");
        return 0;
    }
    catch (const exception &e) {
        cerr << e.what() << endl;
        system("pause");
        return 1;
    }
} else if (fileoption == 'n' || fileoption == 'N') {
//////////////////////////////////////////////////////////////////////
///////////////// 1 strategija
//////////////////////////////////////////////////////////////////////
        char generatefiles;
        cout << "Do you want to generate files? (y/n): " << endl;
        cin >> generatefiles;
        if (generatefiles == 'y' || generatefiles == 'Y') {
            cout << "Enter the number of homework grades: ";
            int numHW;
            cin >> numHW;
            cout << endl;

            char filteroption;
            cout << "Enter filter option ('1' to view students whose average is above 5, '2' for below 5, '3' for both): ";
            cin >> filteroption;
            cout << endl;

            char container;
            cout << "Would you like to view the statistics with vector or list, or both? (v/l/b)" << endl;
            cin >> container;

            char strategy;
            cout << "Which strategy do you want to use (1, 2, 3)?" << endl;
            cin >> strategy;
            if (strategy == '1') {
                if (container == 'V' || container == 'v') {
                    filetimer("studentai_1000.txt", 1000, numHW, Vec1, filteroption);
                    filetimer("studentai_10000.txt", 10000, numHW, Vec1, filteroption);
                    filetimer("studentai_100000.txt", 100000, numHW, Vec1, filteroption);
                    filetimer("studentai_1000000.txt", 1000000, numHW, Vec1, filteroption);
                    filetimer("studentai_10000000.txt", 10000000, numHW, Vec1, filteroption);
                } else if (container == 'L' || container == 'l') {
                    filetimerList("studentai_1000.txt", 1000, numHW, List1, filteroption);
                    filetimerList("studentai_10000.txt", 10000, numHW, List1, filteroption);
                    filetimerList("studentai_100000.txt", 100000, numHW, List1, filteroption);
                    filetimerList("studentai_1000000.txt", 1000000, numHW, List1, filteroption);
                    filetimerList("studentai_10000000.txt", 10000000, numHW, List1, filteroption);
                } else if (container == 'B' || container == 'b') {
                    filetimer("studentai_1000.txt", 1000, numHW, Vec1, filteroption);
                    filetimerList("studentai_1000.txt", 1000, numHW, List1, filteroption);

                    filetimer("studentai_10000.txt", 10000, numHW, Vec1, filteroption);
                    filetimerList("studentai_10000.txt", 10000, numHW, List1, filteroption);

                    filetimer("studentai_100000.txt", 100000, numHW, Vec1, filteroption);
                    filetimerList("studentai_100000.txt", 100000, numHW, List1, filteroption);

                    filetimer("studentai_1000000.txt", 1000000, numHW, Vec1, filteroption);
                    filetimerList("studentai_1000000.txt", 1000000, numHW, List1, filteroption);

                    filetimer("studentai_10000000.txt", 10000000, numHW, Vec1, filteroption);
                    filetimerList("studentai_10000000.txt", 10000000, numHW, List1, filteroption);
                }
        }
            if (strategy == '2') {
                filegeneration("studentai_1000.txt", 1000, numHW, Vec1);
                iteratevector(Vec1, below5);
                savetofile("below5output.txt", below5);
                clearFile("studentai_1000.txt");
                clearFile("below5output.txt");

             //   filegenerationList("studentai_1000.txt", 1000, numHW, List1);
               // iteratelist(List1, below5list);
                //savetofileList("below5output.txt", below5list);
            }
        }
//////////////////////////////////////////////////////////////////////
/////////////////  strattegija
//////////////////////////////////////////////////////////////////////
 else {
    int n;
    do {
        cout << "How many students will you be grading? ";
        cin >> n;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
        } else if (n <= 0) {
            cout << "Invalid input. Please enter a positive number." << endl;
        }
    } while (n <= 0);

    char hw;
    do {
        cout << "Do you know the number of homework assignments per student? (y/n): ";
        cin >> hw;

        if (hw != 'y' && hw != 'Y' && hw != 'n' && hw != 'N') {
            cout << "Invalid input. Please enter 'y' or 'n'." << endl;
            }
        } while (hw != 'y' && hw != 'Y' && hw != 'n' && hw != 'N');

        if (hw == 'y' || hw == 'Y') {
            int hwCount;
            do {
                cout << "Enter the number of assignments: ";
                cin >> hwCount;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number." << endl;
                } else if (hwCount < 0) {
                    cout << "Enter a positive number." << endl;
                } else if (hwCount == 0) {
                    for (int i = 0; i < n; i++) {
                        inputnull(Temp);
                    }
                    cout << "Memory address of student in vector: " << &Vec1.back() << endl;
                    cout << "Memory address of student in list: " << &List1.back() << endl;
                    printHeadernull();
                    for (int i = 0; i < n; i++) {
                        outputnull(Temp);
                    }
                    system("pause");
                    return 0;
                }
            } while (hwCount < 0 && hwCount != 0); // Repeat if input is invalid or negative, exit if 0 is entered


            char random;
            do {
                cout << "Do you want to generate random grades? (y/n): ";
                cin >> random;

                if (random != 'y' && random != 'Y' && random != 'n' && random != 'N') {
                    cout << "Invalid input. Please enter 'y' or 'n'." << endl;
                }
            } while (random != 'y' && random != 'Y' && random != 'n' && random != 'N');

            if (random == 'y' || random == 'Y') {
                for (int i = 0; i < n; i++) {
                    randomgrades(Temp, hwCount);
                    Vec1.push_back(Temp);
                    List1.push_back(Temp);
                    clean(Temp);
                }

                char filteroption;
                cout << "Enter filter option ('1' to print students whose average is above 5, '2' for below 5, '3' for both): ";
                cin >> filteroption;
                char container;
                cout << "Would you like to view the statistics with vector or list, or both? (v/l/b)" << endl;
                cin >> container;
                cout << endl;

//                vector<Stud> below5;
//                vector<Stud> above5;
//                list<Stud> below5list;
//                list<Stud> above5list;

                if (filteroption == '1') {
                    if (container == 'v') {
                        filterabove5(Vec1, above5);
                        savetofile("above5output.txt", above5);
                    }
                    else if (container == 'l') {
                        filterabove5List(List1, above5list);
                        savetofileList("above5output.txt", above5list);
                    }
                    else if (container == 'b') {
                        filterabove5(Vec1, above5);
                        savetofile("above5output.txt", above5);

                        filterabove5List(List1, above5list);
                        savetofileList("above5output.txt", above5list);
                    }

                }
                else if (filteroption == '2') {
                    if (container == 'v') {
                        filterbelow5(Vec1, below5);
                        savetofile("below5output.txt", below5);
                    }
                    else if (container == 'l') {
                        filterbelow5List(List1, below5list);
                        savetofileList("below5output.txt", below5list);
                    }
                    else if (container == 'b') {
                        filterbelow5(Vec1, below5);
                        savetofile("below5output.txt", below5);

                        filterbelow5List(List1, below5list);
                        savetofileList("below5output.txt", below5list);
                    }

                }
                else if (filteroption == '3') {
                    if (container == 'v') {
                        filterbelow5(Vec1, below5);
                        filterabove5(Vec1, above5);
                        savetofile("below5output.txt", below5);
                        savetofile("above5output.txt", above5);
                    }
                    else if (container == 'l') {
                        filterbelow5List(List1, below5list);
                        filterabove5List(List1, above5list);
                        savetofileList("below5output.txt", below5list);
                        savetofileList("above5output.txt", above5list);
                    }
                    else if (container == 'b') {
                        filterbelow5(Vec1, below5);
                        filterabove5(Vec1, above5);
                        savetofile("below5output.txt", below5);
                        savetofile("above5output.txt", above5);

                        filterbelow5List(List1, below5list);
                        filterabove5List(List1, above5list);
                        savetofileList("below5output.txt", below5list);
                        savetofileList("above5output.txt", above5list);
                    }

                }
                cout << "Memory address of student in vector: " << &Vec1.back() << endl;
                cout << "Memory address of student in list: " << &List1.back() << endl;
            } else if (random == 'n' || random == 'N') {
                for (int i = 0; i < n; i++) {
                    input(Temp, hwCount);
                    Vec1.push_back(Temp);
                    List1.push_back(Temp);
                    clean(Temp);
                }
                char filteroption;
                cout << "Enter filter option ('1' to print students whose average is above 5, '2' for below 5, '3' for both): ";
                cin >> filteroption;
                char container;
                cout << "Would you like to view the statistics with vector or list, or both? (v/l/b)" << endl;
                cin >> container;
                cout << endl;

                vector<Stud> below5;
                vector<Stud> above5;
                list<Stud> below5list;
                list<Stud> above5list;
                ofstream belowfile("below5output.txt");
                ofstream abovefile("above5output.txt");

                if (filteroption == '1') {
                    if (container == 'v') {
                        filterabove5(Vec1, above5);
                        outputabove5file(abovefile, above5);
                    } else if (container == 'l') {
                        filterabove5List(List1, above5list);
                        savetofileList("above5output.txt", above5list);
                    } else if (container == 'b') {
                        filterabove5(Vec1, above5);
                        outputabove5file(abovefile, above5);

                        filterabove5List(List1, above5list);
                        savetofileList("above5output.txt", above5list);
                    }

                } else if (filteroption == '2') {
                    if (container == 'v') {
                        filterbelow5(Vec1, below5);
                        outputbelow5file(belowfile, below5);
                    } else if (container == 'l') {
                        filterbelow5List(List1, below5list);
                        savetofileList("below5output.txt", below5list);
                    } else if (container == 'b') {
                        filterbelow5(Vec1, below5);
                        outputbelow5file(belowfile, below5);

                        filterbelow5List(List1, below5list);
                        savetofileList("below5output.txt", below5list);
                    }

                } else if (filteroption == '3') {
                    if (container == 'v') {
                        filterbelow5(Vec1, below5);
                        filterabove5(Vec1, above5);
                        outputbelow5file(belowfile, below5);
                        outputabove5file(abovefile, above5);
                    } else if (container == 'l') {
                        filterbelow5List(List1, below5list);
                        filterabove5List(List1, above5list);
                        savetofileList("below5output.txt", below5list);
                        savetofileList("above5output.txt", above5list);
                    } else if (container == 'b') {
                        filterbelow5(Vec1, below5);
                        filterabove5(Vec1, above5);
                        outputbelow5file(belowfile, below5);
                        outputabove5file(abovefile, above5);

                        filterbelow5List(List1, below5list);
                        filterabove5List(List1, above5list);
                        savetofileList("below5output.txt", below5list);
                        savetofileList("above5output.txt", above5list);
                    }

                }
                cout << "Memory address of student in vector: " << &Vec1.back() << endl;
                cout << "Memory address of student in list: " << &List1.back() << endl;
            }
        } else if (hw == 'n' || hw == 'N') {
            for (int i = 0; i < n; i++) {
                inputgrades(Temp);
                Vec1.push_back(Temp);
                List1.push_back(Temp);
                clean(Temp);
            }
            char filteroption;
                cout << "Enter filter option ('1' to print students whose average is above 5, '2' for below 5, '3' for both): ";
                cin >> filteroption;
                char container;
                cout << "Would you like to view the statistics with vector or list, or both? (v/l/b)" << endl;
                cin >> container;
                cout << endl;

                vector<Stud> below5;
                vector<Stud> above5;
                list<Stud> below5list;
                list<Stud> above5list;
                ofstream belowfile("below5output.txt");
                ofstream abovefile("above5output.txt");

                if (filteroption == '1') {
                    if (container == 'v') {
                        filterabove5(Vec1, above5);
                        outputabove5file(abovefile, above5);
                    } else if (container == 'l') {
                        filterabove5List(List1, above5list);
                        savetofileList("above5output.txt", above5list);
                    } else if (container == 'b') {
                        filterabove5(Vec1, above5);
                        outputabove5file(abovefile, above5);

                        filterabove5List(List1, above5list);
                        savetofileList("above5output.txt", above5list);
                    }

                } else if (filteroption == '2') {
                    if (container == 'v') {
                        filterbelow5(Vec1, below5);
                        outputbelow5file(belowfile, below5);
                    } else if (container == 'l') {
                        filterbelow5List(List1, below5list);
                        savetofileList("below5output.txt", below5list);
                    } else if (container == 'b') {
                        filterbelow5(Vec1, below5);
                        outputbelow5file(belowfile, below5);

                        filterbelow5List(List1, below5list);
                        savetofileList("below5output.txt", below5list);
                    }

                } else if (filteroption == '3') {
                    if (container == 'v') {
                        filterbelow5(Vec1, below5);
                        filterabove5(Vec1, above5);
                        outputbelow5file(belowfile, below5);
                        outputabove5file(abovefile, above5);
                    } else if (container == 'l') {
                        filterbelow5List(List1, below5list);
                        filterabove5List(List1, above5list);
                        savetofileList("below5output.txt", below5list);
                        savetofileList("above5output.txt", above5list);
                    } else if (container == 'b') {
                        filterbelow5(Vec1, below5);
                        filterabove5(Vec1, above5);
                        outputbelow5file(belowfile, below5);
                        outputabove5file(abovefile, above5);

                        filterbelow5List(List1, below5list);
                        filterabove5List(List1, above5list);
                        savetofileList("below5output.txt", below5list);
                        savetofileList("above5output.txt", above5list);
                    }

                }
                cout << "Memory address of student in vector: " << &Vec1.back() << endl;
                cout << "Memory address of student in list: " << &List1.back() << endl;
        return 0;
        }

    }

}
system("pause");

 int option;
    do {
        cout << "Choose option: 1 to view average, 2 to view median: " << endl;

        cin >> option;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        if (option == 1) {
            printHeaderavg();
            sortsurname(Vec1);
            for (Stud student : Vec1) {
                outputavg(student);
            }

            char viewMedian;
            do {
                cout << "Do you want to view the Median as well? (y/n): " << endl;
                cin >> viewMedian;
                if (viewMedian == 'y' || viewMedian == 'Y') {
                    printHeadermed();
                    sortsurname(Vec1);
                    for (Stud student : Vec1) {
                        outputmed(student);
                    }
                } else if (viewMedian != 'n' && viewMedian != 'N') {
                    cout << "Invalid input. Please enter 'y' or 'n'." << endl;
                    }
            } while (viewMedian != 'y' && viewMedian != 'Y' && viewMedian != 'n' && viewMedian != 'N');

        } else if (option == 2) {
            printHeadermed();
            sortsurname(Vec1);
            for (Stud student : Vec1) {
                outputmed(student);
            }

            char viewAverage;
            do {
                cout << "Do you want to view the Average as well? (y/n): " << endl;
                cin >> viewAverage;
                if (viewAverage == 'y' || viewAverage == 'Y') {
                    printHeaderavg();
                    sortsurname(Vec1);
                    for (Stud student : Vec1) {
                        outputavg(student);
                    }
                } else if (viewAverage != 'n' && viewAverage != 'N') {
                    cout << "Invalid input. Please enter 'y' or 'n'." << endl;
                }
            } while (viewAverage != 'y' && viewAverage != 'Y' && viewAverage != 'n' && viewAverage != 'N');
        } else {
            cout << "Invalid option! Please try again." << endl;
        }

    }
    while (option != 1 && option != 2);
system("pause");
    return 0;
}
