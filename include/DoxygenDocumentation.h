#ifndef DOXYGENDOCUMENTATION_H_INCLUDED
#define DOXYGENDOCUMENTATION_H_INCLUDED

/**
 * \mainpage Student App
 *
 * This program works from C++17 onward.
 *
 * This project is a student data entry system that allows the input of student details and grades in various ways, calculates and displays the average and median grades, and lets the user choose how to sort the printed student data.
 *
 * ## Features:
 *
 * ### 1. Data Input:
 * - **Method**: `void inputManual(Studentas& student)`
 *   - **Description**: This method allows the user to manually input student details, such as name, surname, and grades.
 * - **Method**: `generate(int studentCount, int gradeCount, int containerType)`
 *   - **Description**: The user can randomly generate grades for a given student.
 * - **Method**: `inputScan(std::vector<Studentas>& students)` or `inputScan(std::list<Studentas>& students)`
 *   - **Description**: Option to read student data from a file.
 *
 * ### 2. Data Output:
 * - **Method**: `outputManual(const Studentas& student, int avgOrMedian)`
 *   - **Description**: Outputs data to the console.
 * - **Method**: `outputScan(std::vector<Studentas>& students)`
 *   - **Description**: The system can also save student data and calculations to a file.
 *
 * ### 3. Calculations:
 * - The system calculates the average and median based on student grades.
 *
 * ### 4. Sorting Options:
 * - Students can be sorted by different criteria: by name, surname, or average grade.
 *
 * ### 5. Rule of Three:
 * - The code properly handles dynamic memory management with copy constructors, copy assignment operators, and destructors to avoid memory leaks when copying objects.
 *
 * ## .exe File Execution Instructions:
 * 1. Download the `CMakeLists.txt` file from GitHub.
 * 2. Open the terminal in the project folder and type `--cmake CMakeLists.txt`.
 * 3. Then type `--install .`.
 * 4. Next, type `--build .`.
 * 5. Finally, you can find the generated `.exe` file in the `Debug` folder.
 */


#endif // DOXYGENDOCUMENTATION_H_INCLUDED
