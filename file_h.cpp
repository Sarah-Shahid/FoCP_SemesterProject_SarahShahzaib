#include "file_h.h"
#include "structures.h"

#include <fstream>
#include <string>

using namespace std;

// extern globals
extern UserProfile user;

extern Medicine medicines[20];
extern int medicineCount;

extern HealthReading healthReadings[50];
extern int healthCount;

extern MoodEntry moods[30];
extern int moodCount;

extern EmergencyContact contacts[10];
extern int contactCount;

extern Incident incidents[30];
extern int incidentCount;

// ---------------- PROFILE ----------------

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

// ---------------- MEDICINES ----------------

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
    for (int i = 0; i < medicineCount; i++) {
        file << medicines[i].name << "|"
             << medicines[i].dosage << "|"
             << medicines[i].time << "|"
             << medicines[i].takenToday << endl;
    }
}

// ---------------- HEALTH ----------------

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
        file << healthReadings[i].date << "|"
             << healthReadings[i].systolic << "|"
             << healthReadings[i].diastolic << "|"
             << healthReadings[i].sugar << "|"
             << healthReadings[i].heartRate << endl;
    }
}

// ---------------- MOODS ----------------

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

void saveMoods() {
    ofstream file("moods.txt");
    for (int i = 0; i < moodCount; i++) {
        file << moods[i].date << "|"
             << moods[i].mood << "|"
             << moods[i].note << "|"
             << moods[i].score << endl;
    }
}

// ---------------- CONTACTS ----------------

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
        file << contacts[i].name << "|"
             << contacts[i].phone << "|"
             << contacts[i].relation << endl;
    }
}

// ---------------- INCIDENTS ----------------

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
        file << incidents[i].date << "|"
             << incidents[i].type << "|"
             << incidents[i].description << "|"
             << incidents[i].severity << endl;
    }
}

// ---------------- ALL ----------------

void loadAllData() {
    loadProfile();
    loadMedicines();
    loadHealth();
    loadMoods();
    loadContacts();
    loadIncidents();
}

void saveAllData() {
    saveProfile();
    saveMedicines();
    saveHealth();
    saveMoods();
    saveContacts();
    saveIncidents();
}
