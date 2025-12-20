#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <limits>

using namespace std;

// ==================== STRUCTURES ====================

struct UserProfile {
    string name;
    int age;
    string conditions[5];
    int conditionCount;
    string wakeTime;
    string sleepTime;
};

struct Medicine {
    string name;
    string dosage;
    string time;
    bool takenToday;
};

struct HealthReading {
    string date;
    int systolic;
    int diastolic;
    int sugar;
    int heartRate;
};

struct MoodEntry {
    string date;
    string mood;
    string note;
    int score;
};

struct EmergencyContact {
    string name;
    string phone;
    string relation;
};

struct Incident {
    string date;
    string type;
    string description;
    int severity;
};

// ==================== GLOBAL VARIABLES ====================

UserProfile user;
Medicine medicines[20];
int medicineCount = 0;
HealthReading healthReadings[50];
int healthCount = 0;
MoodEntry moods[30];
int moodCount = 0;
EmergencyContact contacts[10];
int contactCount = 0;
Incident incidents[30];
int incidentCount = 0;

string islamicVerses[5] = {
    "Indeed, with hardship comes ease. (Quran 94:6)",
    "And He is with you wherever you are. (Quran 57:4)",
    "So remember Me; I will remember you. (Quran 2:152)",
    "In the remembrance of Allah do hearts find rest. (Quran 13:28)",
    "Allah does not burden a soul beyond that it can bear. (Quran 2:286)"
};

string duas[5] = {
    "Rabbi zidni ilma - My Lord, increase me in knowledge",
    "Allahumma inni as'aluka al-'afiyah - O Allah, I ask You for well-being",
    "Rabbi ishrah li sadri - My Lord, expand for me my chest",
    "Hasbunallahu wa ni'mal wakeel - Allah is sufficient for us",
    "La hawla wa la quwwata illa billah - No power except with Allah"
};

const string CAREGIVER_PIN = "1234";

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
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string date = to_string(ltm->tm_mday) + "/" +
        to_string(1 + ltm->tm_mon) + "/" +
        to_string(1900 + ltm->tm_year);
    return date;
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

// ==================== FILE HANDLING ====================

//this function loads the user profile whenever the program starts.
//all the user info saved in a file will be read using ifstream and then shown on the console.
void loadProfile() {
    ifstream file("profile.txt");
    if (file.is_open()) {
        getline(file, user.name);
        file >> user.age;
        file.ignore();
        file >> user.conditionCount;
        file.ignore();
        for (int i = 0; i < user.conditionCount; i++) {
            getline(file, user.conditions[i]);
        }
        getline(file, user.wakeTime);
        getline(file, user.sleepTime);
    }
}

//this function uses the data inside variables then stores (write) it into the file.
void saveProfile() {
    ofstream file("profile.txt");
    file << user.name << endl;
    file << user.age << endl;
    file << user.conditionCount << endl;
    for (int i = 0; i < user.conditionCount; i++) {
        file << user.conditions[i] << endl;
    }
    file << user.wakeTime << endl;
    file << user.sleepTime << endl;
}

void loadMedicines() {
    ifstream file("medicines.txt");
    medicineCount = 0;
    if (file.is_open()) {
        while (file >> ws && getline(file, medicines[medicineCount].name, '|')) {
            getline(file, medicines[medicineCount].dosage, '|');
            getline(file, medicines[medicineCount].time, '|');
            file >> medicines[medicineCount].takenToday;
            file.ignore();
            medicineCount++;
            if (medicineCount >= 20) break;
        }
    }
}

void saveMedicines() {
    ofstream file("medicines.txt");
    for (int i = 0; i < medicineCount; i++) 
    {
        file << medicines[i].name << "|" << medicines[i].dosage << "|"
            << medicines[i].time << "|" << medicines[i].takenToday << endl;
    }
}

void loadHealth() {
    ifstream file("health.txt");
    healthCount = 0;
    if (file.is_open()) {
        while (file >> ws && getline(file, healthReadings[healthCount].date, '|')) {
            file >> healthReadings[healthCount].systolic;
            file.ignore();
            file >> healthReadings[healthCount].diastolic;
            file.ignore();
            file >> healthReadings[healthCount].sugar;
            file.ignore();
            file >> healthReadings[healthCount].heartRate;
            file.ignore();
            healthCount++;
            if (healthCount >= 50) break;
        }
    }
}

void saveHealth() {
    ofstream file("health.txt");
    for (int i = 0; i < healthCount; i++) {
        file << healthReadings[i].date << "|" << healthReadings[i].systolic << "|"
            << healthReadings[i].diastolic << "|" << healthReadings[i].sugar << "|"
            << healthReadings[i].heartRate << endl;
    }
}

void loadMoods() {
    ifstream file("moods.txt");
    moodCount = 0;
    if (file.is_open()) {
        while (file >> ws && getline(file, moods[moodCount].date, '|')) {
            getline(file, moods[moodCount].mood, '|');
            getline(file, moods[moodCount].note, '|');
            file >> moods[moodCount].score;
            file.ignore();
            moodCount++;
            if (moodCount >= 30) break;
        }
    }
}

//writing mood summary into the file.
void saveMoods() {
    ofstream file("moods.txt");
    for (int i = 0; i < moodCount; i++) {
        file << moods[i].date << "|" << moods[i].mood << "|"
            << moods[i].note << "|" << moods[i].score << endl;
    }
}

//read contact information from the file and store it into the right arrays.
void loadContacts() {
    ifstream file("contacts.txt");
    contactCount = 0;
    if (file.is_open()) {
        while (file >> ws && getline(file, contacts[contactCount].name, '|')) {
            getline(file, contacts[contactCount].phone, '|');
            getline(file, contacts[contactCount].relation);
            contactCount++;
            if (contactCount >= 10) break;
        }
    }
}

void saveContacts() {
    ofstream file("contacts.txt");
    for (int i = 0; i < contactCount; i++) {
        file << contacts[i].name << "|" << contacts[i].phone << "|"
            << contacts[i].relation << endl;
    }
}

void loadIncidents() {
    ifstream file("incidents.txt");
    incidentCount = 0;
    if (file.is_open()) {
        while (file >> ws && getline(file, incidents[incidentCount].date, '|')) {
            getline(file, incidents[incidentCount].type, '|');
            getline(file, incidents[incidentCount].description, '|');
            file >> incidents[incidentCount].severity;
            file.ignore();
            incidentCount++;
            if (incidentCount >= 30) break;
        }
    }
}

void saveIncidents() {
    ofstream file("incidents.txt");
    for (int i = 0; i < incidentCount; i++) {
        file << incidents[i].date << "|" << incidents[i].type << "|"
            << incidents[i].description << "|" << incidents[i].severity << endl;
    }
}

//at the start of program, it loads everything that was saved in the last run.
void loadAllData() 
{
    loadProfile();
    loadMedicines();
    loadHealth();
    loadMoods();
    loadContacts();
    loadIncidents();
}

void saveAllData() 
{
    saveProfile();
    saveMedicines();
    saveHealth();
    saveMoods();
    saveContacts();
    saveIncidents();
}


// ==================== MODULE 1: USER PROFILE ====================
//managing the creation/ editing of user profile.

void createProfile() {
    clearScreen();
    printHeader("CREATE USER PROFILE");

    cout << "Enter your name: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, user.name); //name input is taken using getline so full name can be entered.

    cout << "Enter your age: ";
    cin >> user.age;

    cout << "How many medical conditions? (0-5): ";
    cin >> user.conditionCount;
    if (user.conditionCount < 0) user.conditionCount = 0; //conditions less than 0 are made 0.
    if (user.conditionCount > 5) user.conditionCount = 5; //conditons greater than 5 and rounded down to 5.
    cin.ignore();

    //loop runs until the user writes all medical conditions
    //which are equal to the conditioncount int stored in a struct.
    for (int i = 0; i < user.conditionCount; i++) 
    {
        cout << "Condition " << (i + 1) << ": ";
        getline(cin, user.conditions[i]);
    }

    cout << "Wake-up time (e.g., 06:00): ";
    getline(cin, user.wakeTime);

    cout << "Sleep time (e.g., 22:00): ";
    getline(cin, user.sleepTime);

    saveProfile(); //this function is called so that all the data the user has entered can be saved into the profile.txt file.
    cout << "\nProfile created.\n";
    pauseScreen();
}

void viewProfile() {
    clearScreen();
    printHeader("USER PROFILE");

    cout << "Name: " << user.name << endl;
    cout << "Age: " << user.age << endl;
    cout << "Medical Conditions: ";
    for (int i = 0; i < user.conditionCount; i++) {
        cout << user.conditions[i];
        if (i < user.conditionCount - 1) cout << ", ";
    }
    cout << "\nWake Time: " << user.wakeTime << endl;
    cout << "Sleep Time: " << user.sleepTime << endl;

    pauseScreen();
}

void profileMenu() {
    int choice;
    do {
        clearScreen(); //to clear the previous console outputs.
        printHeader("PROFILE MENU");
        cout << "1. View Profile\n";
        cout << "2. Edit Profile\n";
        cout << "0. Back\n";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: viewProfile(); break;
        case 2: createProfile(); break;
        default: break;
        }
    } while (choice != 0);
    //let the loop run until the user presses 0 to go to the previous page.
}

// ==================== MODULE 2: MEDICINE REMINDER ====================

void checkMedicineReminders() {
    cout << "\nPending medicine reminders:\n";
    bool found = false;
    for (int i = 0; i < medicineCount; i++) {
        if (!medicines[i].takenToday) {
            cout << "- " << medicines[i].name << " (" << medicines[i].dosage
                 << ") at " << medicines[i].time << endl;
            found = true;
        }
    }
    if (!found) cout << "All medicines taken for today.\n";
}

void addMedicine() {
    clearScreen();
    printHeader("ADD MEDICINE");

    if (medicineCount >= 20) {
        cout << "Medicine list is full.\n";
        pauseScreen();
        return;
    }

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Medicine name: ";
    getline(cin, medicines[medicineCount].name);

    cout << "Dosage (e.g., 500mg): ";
    getline(cin, medicines[medicineCount].dosage);

    cout << "Time (e.g., 08:00): ";
    getline(cin, medicines[medicineCount].time);

    medicines[medicineCount].takenToday = false;
    medicineCount++;

    saveMedicines();
    cout << "\nMedicine added.\n";
    pauseScreen();
}

void viewMedicines() {
    clearScreen();
    printHeader("ALL MEDICINES");

    if (medicineCount == 0) {
        cout << "No medicines added.\n";
    } else {
        for (int i = 0; i < medicineCount; i++) {
            cout << (i + 1) << ". " << medicines[i].name << " - "
                 << medicines[i].dosage << " at " << medicines[i].time << endl;
        }
    }
    pauseScreen();
}

void markMedicineTaken() {
    clearScreen();
    printHeader("MARK MEDICINE AS TAKEN");

    if (medicineCount == 0) {
        cout << "No medicines added.\n";
        pauseScreen();
        return;
    }

    for (int i = 0; i < medicineCount; i++) {
        cout << (i + 1) << ". " << medicines[i].name << " - "
             << (medicines[i].takenToday ? "Taken" : "Not taken") << endl;
    }

    int choice;
    cout << "\nEnter medicine number (0 to cancel): ";
    cin >> choice;

    if (choice > 0 && choice <= medicineCount) {
        medicines[choice - 1].takenToday = true;
        saveMedicines();
        cout << "\nMarked as taken.\n";
    }
    pauseScreen();
}

void weeklyAdherenceReport() {
    clearScreen();
    printHeader("TODAY'S MEDICINE ADHERENCE");

    int total = medicineCount;
    int taken = 0;

    for (int i = 0; i < medicineCount; i++) {
        if (medicines[i].takenToday) taken++;
    }

    if (total > 0) {
        float percentage = (float)taken / total * 100.0f;
        cout << "Taken: " << taken << "/" << total
             << " (" << fixed << setprecision(1) << percentage << "%)\n";

        if (percentage >= 90)      cout << "Excellent adherence.\n";
        else if (percentage >= 70) cout << "Good, try to reach 100%.\n";
        else                       cout << "Low adherence, please be careful.\n";
    } else {
        cout << "No medicines defined.\n";
    }
    pauseScreen();
}

void medicineMenu() {
    int choice;
    do {
        clearScreen();
        printHeader("MEDICINE REMINDER");
        cout << "1. Add Medicine\n";
        cout << "2. View Medicines\n";
        cout << "3. Today's Reminders\n";
        cout << "4. Mark as Taken\n";
        cout << "5. Today Adherence Report\n";
        cout << "0. Back\n";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: addMedicine(); break;
        case 2: viewMedicines(); break;
        case 3:
            clearScreen();
            printHeader("TODAY'S REMINDERS");
            checkMedicineReminders();
            pauseScreen();
            break;
        case 4: markMedicineTaken(); break;
        case 5: weeklyAdherenceReport(); break;
        default: break;
        }
    } while (choice != 0);
}

// ==================== MODULE 3: HEALTH TRACKER ====================

void analyzeHealth(HealthReading& r) {
    cout << "\nAnalysis:\n";

    if (r.systolic > 140 || r.diastolic > 90) {
        cout << "- High blood pressure. Rest, reduce salt, consider doctor.\n";
    } else if (r.systolic < 90 || r.diastolic < 60) {
        cout << "- Low blood pressure. Rest and elevate legs.\n";
    } else {
        cout << "- Blood pressure: normal.\n";
    }

    if (r.sugar > 180) {
        cout << "- High sugar. Avoid sweets, drink water.\n";
    } else if (r.sugar < 70) {
        cout << "- Low sugar. Take something sweet and inform caregiver.\n";
    } else {
        cout << "- Blood sugar: normal.\n";
    }

    if (r.heartRate > 100) {
        cout << "- High heart rate. Sit and breathe slowly.\n";
    } else if (r.heartRate < 60) {
        cout << "- Low heart rate. Monitor closely.\n";
    } else {
        cout << "- Heart rate: normal.\n";
    }
}

void addHealthReading() {
    clearScreen();
    printHeader("ADD HEALTH READING");

    if (healthCount >= 50) {
        cout << "Health log is full.\n";
        pauseScreen();
        return;
    }

    healthReadings[healthCount].date = getCurrentDate();

    cout << "Systolic BP: ";
    cin >> healthReadings[healthCount].systolic;

    cout << "Diastolic BP: ";
    cin >> healthReadings[healthCount].diastolic;

    cout << "Sugar (mg/dL): ";
    cin >> healthReadings[healthCount].sugar;

    cout << "Heart rate (bpm): ";
    cin >> healthReadings[healthCount].heartRate;

    analyzeHealth(healthReadings[healthCount]);
    healthCount++;
    saveHealth();

    cout << "\nReading saved.\n";
    pauseScreen();
}

void viewHealthReadings() {
    clearScreen();
    printHeader("HEALTH HISTORY");

    if (healthCount == 0) {
        cout << "No readings yet.\n";
    } else {
        for (int i = healthCount - 1; i >= 0 && i >= healthCount - 10; i--) {
            cout << "\n----------------------------------------\n";
            cout << "Date: " << healthReadings[i].date << endl;
            cout << "BP: " << healthReadings[i].systolic << "/"
                 << healthReadings[i].diastolic << " mmHg\n";
            cout << "Sugar: " << healthReadings[i].sugar << " mg/dL\n";
            cout << "Heart rate: " << healthReadings[i].heartRate << " bpm\n";
        }
    }
    pauseScreen();
}

void weeklyHealthAverage() {
    clearScreen();
    printHeader("LAST WEEK AVERAGE");

    if (healthCount == 0) {
        cout << "No readings available.\n";
        pauseScreen();
        return;
    }

    int count = (healthCount < 7) ? healthCount : 7;
    int s = 0, d = 0, su = 0, hr = 0;

    for (int i = healthCount - 1; i >= healthCount - count; i--) {
        s   += healthReadings[i].systolic;
        d   += healthReadings[i].diastolic;
        su  += healthReadings[i].sugar;
        hr  += healthReadings[i].heartRate;
    }

    cout << "Average BP: " << s / count << "/" << d / count << " mmHg\n";
    cout << "Average sugar: " << su / count << " mg/dL\n";
    cout << "Average heart rate: " << hr / count << " bpm\n";

    pauseScreen();
}

void healthMenu() {
    int choice;
    do {
        clearScreen();
        printHeader("HEALTH TRACKER");
        cout << "1. Add Today's Reading\n";
        cout << "2. View Readings\n";
        cout << "3. Weekly Average\n";
        cout << "0. Back\n";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: addHealthReading(); break;
        case 2: viewHealthReadings(); break;
        case 3: weeklyHealthAverage(); break;
        default: break;
        }
    } while (choice != 0);
}


int main()
{

    return 0;
}