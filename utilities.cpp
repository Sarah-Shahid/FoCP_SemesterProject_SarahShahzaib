#include "utilities.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

// ==================== UTILITY FUNCTIONS ====================

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return to_string(ltm->tm_mday) + "/" +
           to_string(1 + ltm->tm_mon) + "/" +
           to_string(1900 + ltm->tm_year);
}

string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    string hour = (ltm->tm_hour < 10 ? "0" : "") + to_string(ltm->tm_hour);
    string minute = (ltm->tm_min < 10 ? "0" : "") + to_string(ltm->tm_min);

    return hour + ":" + minute;
}

void printHeader(const string& title) {
    cout << "\n============================================================\n";
    cout << title << "\n";
    cout << "============================================================\n\n";
}
