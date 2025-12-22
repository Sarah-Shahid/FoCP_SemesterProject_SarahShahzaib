
#include <iostream>
#include "structures.h"
#include "file_h.h"
#include "utilities.h"
#include "globals.h"
#include "modules.h"

#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <limits>

using namespace std;

// ==================== MAIN FUNCTION ====================

int main() {
    srand((unsigned)time(0));
    loadAllData();

    if (user.name.empty()) {
        clearScreen();
        printHeader("ELDER CARE DIGITAL ASSISTANT");
        cout << "First time setup: Please create your profile.\n";
        pauseScreen();
        createProfile();
    }

    mainMenu();
    return 0;
}