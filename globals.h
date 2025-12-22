#ifndef GLOBALS_H
#define GLOBALS_H

#include "structures.h"
#include <string>

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

extern std::string islamicVerses[5];
extern std::string duas[5];
extern const std::string CAREGIVER_PIN;

#endif
