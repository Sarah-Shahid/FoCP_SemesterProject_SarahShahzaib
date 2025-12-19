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


int main(){

    return 0;
}