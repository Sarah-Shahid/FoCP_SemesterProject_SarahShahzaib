#ifndef MODULES_H
#define MODULES_H

// ===== Profile =====
void createProfile();
void viewProfile();
void profileMenu();

// ===== Medicine =====
void checkMedicineReminders();
void addMedicine();
void viewMedicines();
void markMedicineTaken();
void weeklyAdherenceReport();
void medicineMenu();

// ===== Health =====
void addHealthReading();
void viewHealthReadings();
void weeklyHealthAverage();
void healthMenu();

// ===== Mood =====
void addMoodEntry();
void viewMoodTrend();
void moodMenu();

// ===== Islamic =====
void islamicMenu();

// ===== Daily Routine =====
void dailyRoutineMenu();

// ===== Emergency =====
void displayEmergencyContacts();
void addEmergencyContact();
void emergencyMenu();

// ===== Incidents =====
void logIncident();
void viewIncidents();
void incidentMenu();

// ===== Games =====
void guessTheNumber();
void quickMath();
void gamesMenu();

// ===== Symptom Checker =====
void symptomChecker();

// ===== Caregiver =====
void caregiverWeeklySummary();
void caregiverMenu();

// ===== Main Menu =====
void displayWelcome();
void mainMenu();

#endif
