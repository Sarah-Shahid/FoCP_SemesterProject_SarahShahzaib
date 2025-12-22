#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
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

#endif
