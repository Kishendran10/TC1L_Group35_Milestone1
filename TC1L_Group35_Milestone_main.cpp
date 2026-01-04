// *******************
// Program: AttendanceTracker_M1.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT4L
// Trimester: 2530
// Member_1: 252UC242M9 | KISHENDRAN A/L YOGALINGAM | KISHENDRAN.YOGALINGAM1@student.mmu.edu.my | 0122976330
// Member_2: 252UC242Q6 | VIKKESH A/L GANESAN | VIKKESH.GANESAN1@student.mmu.edu.my | 0173068254
// Member_3: 252UC25505 | SAGAD MOHAMEDSALIH MAGZOB | SAGAD.MOHAMEDSALIH.MAGZOB@student.mmu.edu.my | 01111212934
// Member_4: 243UC2468W | AZZAM T.H.AYESH | AZZAM.T.H.@student.mmu.edu.my | +966500529151
// ******************

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

const int MAX_COLS = 10;
const int MAX_ROWS = 100;

string sheetName;
string colName[MAX_COLS];
string colType[MAX_COLS];
string table[MAX_ROWS][MAX_COLS];

int colCount = 0;
int rowCount = 0;

// ===== Function Prototypes =====
bool isNumber(const string&);
bool hasAlphabet(const string&);
bool isStatusColumn(string);
string toLower(string);

void showIntro();
void createSheet();
void defineColumns();
void insertRows();
void displayCSV();

// ===== MAIN =====
int main() {
    showIntro();
    createSheet();
    defineColumns();
    insertRows();
    displayCSV();
    return 0;
}

// ===== FUNCTIONS =====

void showIntro() {
    cout << "===========================================\n";
    cout << " STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "===========================================\n\n";

    cout << "INPUT RULES:\n";
    cout << "- INT columns   : Numbers only\n";
    cout << "- TEXT columns  : Must contain letters\n";
    cout << "- Status column : ONLY 'in class' or 'not in class'\n";
    cout << "===========================================\n\n";
}

void createSheet() {
    cout << "[ SHEET CREATION ]\n";
    cout << "Enter attendance sheet name: ";
    getline(cin, sheetName);

    while (sheetName.empty()) {
        cout << "ERROR: Sheet name cannot be empty. Enter again: ";
        getline(cin, sheetName);
    }

    cout << "Sheet \"" << sheetName << "\" created successfully.\n\n";
}

void defineColumns() {
    cout << "[ SHEET STRUCTURE SETUP ]\n";

    do {
        cout << "Number of columns (1-10): ";
        cin >> colCount;
        cin.ignore();
    } while (colCount < 1 || colCount > 10);

    for (int i = 0; i < colCount; i++) {
        cout << "\nColumn " << i + 1 << " name: ";
        getline(cin, colName[i]);

        while (colName[i].empty()) {
            cout << "ERROR: Column name cannot be empty. Enter again: ";
            getline(cin, colName[i]);
        }

        do {
            cout << "Column type (INT / TEXT): ";
            getline(cin, colType[i]);
            for (char &c : colType[i]) c = toupper(c);
        } while (colType[i] != "INT" && colType[i] != "TEXT");
    }

    cout << "\nSHEET SETUP COMPLETE\n";
    cout << "-------------------------------------------\n";
    for (int i = 0; i < colCount; i++) {
        cout << i + 1 << ". " << colName[i]
             << " (" << colType[i] << ")\n";
    }
    cout << "-------------------------------------------\n\n";
}

void insertRows() {
    char choice = 'y';

    cout << "[ ADDING ATTENDANCE RECORDS ]\n";

    while ((choice == 'y' || choice == 'Y') && rowCount < MAX_ROWS) {
        cout << "\n--- Record " << rowCount + 1 << " ---\n";

        for (int i = 0; i < colCount; i++) {
            string input;
            bool valid = false;

            while (!valid) {
                if (isStatusColumn(colName[i])) {
                    cout << colName[i] << " (in class / not in class): ";
                } else {
                    cout << colName[i] << ": ";
                }

                getline(cin, input);

                if (input.empty()) {
                    cout << "ERROR: Input cannot be empty.\n";
                    continue;
                }

                if (colType[i] == "INT" && !isNumber(input)) {
                    cout << "ERROR: Numbers only allowed.\n";
                    continue;
                }

                if (colType[i] == "TEXT"
                    && !isStatusColumn(colName[i])
                    && !hasAlphabet(input)) {
                    cout << "ERROR: Must contain letters.\n";
                    continue;
                }

                if (isStatusColumn(colName[i])) {
                    string temp = toLower(input);
                    if (temp == "in class") input = "In Class";
                    else if (temp == "not in class") input = "Not In Class";
                    else {
                        cout << "ERROR: Use 'in class' or 'not in class' only.\n";
                        continue;
                    }
                }

                valid = true;
            }

            table[rowCount][i] = input;
        }

        rowCount++;
        cout << "Record added successfully.\n";

        cout << "Add another record? (y/n): ";
        cin >> choice;
        cin.ignore();
    }
}

void displayCSV() {
    cout << "\n===========================================\n";
    cout << " FINAL ATTENDANCE SHEET (CSV FORMAT)\n";
    cout << "===========================================\n\n";

    for (int i = 0; i < colCount; i++) {
        cout << left << setw(18) << colName[i];
        if (i < colCount - 1) cout << ", ";
    }
    cout << "\n-------------------------------------------\n";

    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            cout << left << setw(18) << table[r][c];
            if (c < colCount - 1) cout << ", ";
        }
        cout << "\n";
    }

    cout << "\n===========================================\n";
    cout << " END OF PROGRAM\n";
    cout << "===========================================\n";
}

// ===== HELPER FUNCTIONS =====

bool isNumber(const string& s) {
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

bool hasAlphabet(const string& s) {
    for (char c : s)
        if (isalpha(c)) return true;
    return false;
}

bool isStatusColumn(string name) {
    name = toLower(name);
    return name.find("status") != string::npos;
}

string toLower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}


