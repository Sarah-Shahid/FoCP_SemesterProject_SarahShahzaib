#include "globals.h"

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

std::string islamicVerses[5] = {
    "Indeed, with hardship comes ease. (Quran 94:6)",
    "And He is with you wherever you are. (Quran 57:4)",
    "So remember Me; I will remember you. (Quran 2:152)",
    "In the remembrance of Allah do hearts find rest. (Quran 13:28)",
    "Allah does not burden a soul beyond that it can bear. (Quran 2:286)"
};

std::string duas[5] = {
    "Rabbi zidni ilma - My Lord, increase me in knowledge",
    "Allahumma inni as'aluka al-'afiyah - O Allah, I ask You for well-being",
    "Rabbi ishrah li sadri - My Lord, expand for me my chest",
    "Hasbunallahu wa ni'mal wakeel - Allah is sufficient for us",
    "La hawla wa la quwwata illa billah - No power except with Allah"
};

const std::string CAREGIVER_PIN = "1234";
