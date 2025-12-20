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


int main()
{

    return 0;
}