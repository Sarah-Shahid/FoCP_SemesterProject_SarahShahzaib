#include "structures.h"  
#include "file_h.h"      
#include "utilities.h"
#include "modules.h"
#include "globals.h"

#include <iostream>      
#include <fstream>       
#include <string>        
#include <ctime>         
#include <cstdlib>       
#include <iomanip>       
#include <limits>        


// ==================== MODULE 1: USER PROFILE ====================

void createProfile() {
    clearScreen();
    printHeader("CREATE USER PROFILE");

    cout << "\x1b[32m";
    cout << "Enter your name: ";
    cout << "\x1b[0m";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, user.name);
     
    cout << "\x1b[32m";
    cout << "Enter your age: ";
    cout << "\x1b[0m";
    cin >> user.age;

    cout << "\x1b[32m";
    cout << "How many medical conditions? (0-5): ";
    cout << "\x1b[0m";
    cin >> user.conditionCount;
    if (user.conditionCount < 0) user.conditionCount = 0;
    if (user.conditionCount > 5) user.conditionCount = 5;
    cin.ignore();

    cout << endl;
    for (int i = 0; i < user.conditionCount; i++) {
        cout << "\x1b[32m";
        cout << "Condition " << (i + 1) << ": ";
        cout << "\x1b[0m";
        getline(cin, user.conditions[i]);
    }

    cout << endl;
    cout << "\x1b[32m";
    cout << "Wake-up time (e.g: 06:00): ";
    cout << "\x1b[0m";
    getline(cin, user.wakeTime);

    cout << "\x1b[32m";
    cout << "Sleep time (e.g: 22:00): ";
    cout << "\x1b[0m";
    getline(cin, user.sleepTime);

    saveProfile();
    cout << "\nProfile created.\n";
    pauseScreen();
}

void viewProfile() {
    clearScreen();
    printHeader("USER PROFILE");

    cout << "\x1b[32m";
    cout << "NAME: " << user.name << endl;
    cout << "AGE: " << user.age << endl;
    cout << "MEDICAL CONDITIONS: ";
    for (int i = 0; i < user.conditionCount; i++) {
        cout << user.conditions[i];
        if (i < user.conditionCount - 1) cout << ", ";
    }
    cout << "\nWAKE TIME: " << user.wakeTime << endl;
    cout << "SLEEP TIME: " << user.sleepTime << endl;
    cout << "\x1b[0m";

    pauseScreen();
}

void profileMenu() {
    int choice;
    do {
        clearScreen();
        printHeader("PROFILE MENU");
        cout << "\x1b[32m";
        cout << "1. View Profile\n";
        cout << "2. Edit Profile\n";
        cout << "\x1b[0m";
        cout << "0. Back\n";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: viewProfile(); break;
        case 2: createProfile(); break;
        default: break;
        }
    } while (choice != 0);
}

// ==================== MODULE 2: MEDICINE REMINDER ====================

void checkMedicineReminders() {
    cout << "\x1b[35m";
    cout << "Pending medicine reminders:\n\n";
    cout << "\x1b[0m";

    bool found = false;
    for (int i = 0; i < medicineCount; i++) {
        if (!medicines[i].takenToday) {
            cout << "- " << "\x1b[35m" << medicines[i].name << " (" << medicines[i].dosage
                << ") at " << medicines[i].time << endl;
            cout << "\x1b[0m";
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
    cout << "\x1b[35m";
    cout << "Medicine name: ";
    cout << "\x1b[0m";
    getline(cin, medicines[medicineCount].name);

    cout << "\x1b[35m";
    cout << "Dosage (e.g., 500mg): ";
    cout << "\x1b[0m";
    getline(cin, medicines[medicineCount].dosage);

    cout << "\x1b[35m";
    cout << "Time (e.g., 08:00): ";
    cout << "\x1b[0m";
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
    }
    else {
        
        for (int i = 0; i < medicineCount; i++) {
            cout << (i + 1) << ". " << "\x1b[35m" << medicines[i].name << " - "
                << medicines[i].dosage << " at " << medicines[i].time << endl;
            cout << "\x1b[0m";
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
        cout << (i + 1) << ". " << "\x1b[35m" << medicines[i].name << "\x1b[0m" << " - "
            << (medicines[i].takenToday ? "Taken" : "Not taken") << endl;
    }

    int choice;
    cout << "\x1b[35m";
    cout << "\nEnter medicine number (0 to cancel): ";
    cout << "\x1b[0m";
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
        cout << "\x1b[35m";
        cout << "Taken: " << taken << "/" << total
            << ", " << fixed << setprecision(1) << percentage << "%.\n";

        if (percentage >= 90)      cout << "Excellent adherence.\n";
        else if (percentage >= 70) cout << "Good, try to reach 100%.\n";
        else                       cout << "Low adherence, please be careful.\n";
        cout << "\x1b[0m";
    }
    else {
        cout << "No medicines defined.\n";
    }
    pauseScreen();
}

void medicineMenu() {
    int choice;
    do {
        clearScreen();
        printHeader("MEDICINE REMINDER");

        cout << "\x1b[35m";
        cout << "1. Add Medicine\n";
        cout << "2. View Medicines\n";
        cout << "3. Today's Reminders\n";
        cout << "4. Mark as Taken\n";
        cout << "5. Today Adherence Report\n";
        cout << "\x1b[0m";    // reset
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
    cout << "\n== ( ANALYSIS )==\n";

    cout << "\x1b[33m";
    if (r.systolic > 140 || r.diastolic > 90) {
        cout << "- High blood pressure. Rest, reduce salt, consider doctor.\n";
    }
    else if (r.systolic < 90 || r.diastolic < 60) {
        cout << "- Low blood pressure. Rest and elevate legs.\n";
    }
    else {
        cout << "- Blood pressure: normal.\n";
    }

    if (r.sugar > 180) {
        cout << "- High sugar. Avoid sweets, drink water.\n";
    }
    else if (r.sugar < 70) {
        cout << "- Low sugar. Take something sweet and inform caregiver.\n";
    }
    else {
        cout << "- Blood sugar: normal.\n";
    }

    if (r.heartRate > 100) {
        cout << "- High heart rate. Sit and breathe slowly.\n";
    }
    else if (r.heartRate < 60) {
        cout << "- Low heart rate. Monitor closely.\n";
    }
    else {
        cout << "- Heart rate: normal.\n";
    }
    cout << "\x1b[0m";
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

    cout << "\x1b[33m";
    cout << "Systolic BP: ";
    cout << "\x1b[0m";
    cin >> healthReadings[healthCount].systolic;

    cout << "\x1b[33m";
    cout << "Diastolic BP: ";
    cout << "\x1b[0m";
    cin >> healthReadings[healthCount].diastolic;

    cout << "\x1b[33m";
    cout << "Sugar (mg/dL): ";
    cout << "\x1b[0m";
    cin >> healthReadings[healthCount].sugar;

    cout << "\x1b[33m";
    cout << "Heart rate (bpm): ";
    cout << "\x1b[0m";
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
    }
    else {
        for (int i = healthCount - 1; i >= 0 && i >= healthCount - 10; i--) {
            cout << "------------------------------------\n";
            cout << "\x1b[33m";
            cout << "DATE: " << healthReadings[i].date << endl << endl;
            cout << "BP: " << healthReadings[i].systolic << "/"
                << healthReadings[i].diastolic << " mmHg\n";
            cout << "SUGAR: " << healthReadings[i].sugar << " mg/dL\n";
            cout << "HEART RATE: " << healthReadings[i].heartRate << " bpm\n";
            cout << "\x1b[0m";
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
        s += healthReadings[i].systolic;
        d += healthReadings[i].diastolic;
        su += healthReadings[i].sugar;
        hr += healthReadings[i].heartRate;
    }

    cout << "\x1b[33m";
    cout << "Average BP: " << s / count << "/" << d / count << " mmHg\n";
    cout << "Average sugar: " << su / count << " mg/dL\n";
    cout << "Average heart rate: " << hr / count << " bpm\n";
    cout << "\x1b[0m";

    pauseScreen();
}

void healthMenu() {
    int choice;
    do {
        clearScreen();
        printHeader("HEALTH TRACKER");
        cout << "\x1b[33m";
        cout << "1. Add Today's Reading\n";
        cout << "2. View Readings\n";
        cout << "3. Weekly Average\n";
        cout << "\x1b[0m";
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

// ==================== MODULE 4: MOOD & JOURNALING ====================

int analyzeSentiment(string mood, const string& note) {
    int score = 3;
    if (mood == "happy") score = 5;
    else if (mood == "tired") score = 2;
    else if (mood == "sad" || mood == "anxious") score = 1;

    string negative[] = { "pain", "alone", "worried", "scared", "bad" };
    string positive[] = { "better", "good", "family", "blessed", "happy" };

    for (int i = 0; i < 5; i++) {
        if (note.find(negative[i]) != string::npos) score--;
        if (note.find(positive[i]) != string::npos) score++;
    }

    if (score < 1) score = 1;
    if (score > 5) score = 5;
    return score;
}

void addMoodEntry() {
    clearScreen();
    printHeader("LOG MOOD");

    if (moodCount >= 30) {
        cout << "Mood log is full.\n";
        pauseScreen();
        return;
    }

    moods[moodCount].date = getCurrentDate();

    cout << "\x1b[36m";
    cout << "--> How are you feeling today?\n";
    cout << "1. Happy\n2. Okay\n3. Tired\n4. Sad\n5. Anxious\n\n";
    cout << "\x1b[0m";

    cout << "Choice: ";

    int c;
    cin >> c;
    cin.ignore();

    switch (c) {
    case 1: moods[moodCount].mood = "happy"; break;
    case 2: moods[moodCount].mood = "okay"; break;
    case 3: moods[moodCount].mood = "tired"; break;
    case 4: moods[moodCount].mood = "sad"; break;
    case 5: moods[moodCount].mood = "anxious"; break;
    default: moods[moodCount].mood = "okay";
    }

    cout << "\x1b[36m";
    cout << "\nNOTE (optional): ";
    cout << "\x1b[0m";
    getline(cin, moods[moodCount].note);

    moods[moodCount].score =
        analyzeSentiment(moods[moodCount].mood, moods[moodCount].note);

    cout << "\x1b[36m";
    cout << "\nMood score: " << moods[moodCount].score << "/5\n";
    cout << "\x1b[0m";

    moodCount++;
    saveMoods();

    pauseScreen();
}

void viewMoodTrend() {
    clearScreen();
    printHeader("MOOD TREND (LAST WEEK)");

    if (moodCount == 0) {
        cout << "No mood entries.\n";
        pauseScreen();
        return;
    }

    int happy = 0, sad = 0, anxious = 0;
    float avg = 0.0f;
    int count = (moodCount < 7) ? moodCount : 7;

    for (int i = moodCount - 1; i >= moodCount - count; i--) {
        if (moods[i].mood == "happy")   happy++;
        if (moods[i].mood == "sad")     sad++;
        if (moods[i].mood == "anxious") anxious++;
        avg += moods[i].score;
    }
   
    avg /= count;
    cout << "\x1b[36m" << "Happy days: " << "\x1b[0m" << happy << endl;
    cout << "\x1b[36m" << "Sad days: " << "\x1b[0m" << sad << endl;
    cout << "\x1b[36m" << "Anxious days: " << "\x1b[0m" << anxious << endl << endl;
    cout << "\x1b[36m" << "Average score: " << "\x1b[0m" << fixed << setprecision(1) << avg << "/5\n";

    if (sad >= 4 || anxious >= 3)
        cout << "\x1b[36m" << "\nWARNING: Frequent low mood. Consider talking to family or doctor.\n" << "\x1b[0m";

    pauseScreen();
}

void moodMenu() {
    int choice;
    do {
        clearScreen();
        printHeader("MOOD AND JOURNAL");
        cout << "\x1b[36m";
        cout << "1. Log Mood\n";
        cout << "2. View Last 7 Entries\n";
        cout << "3. Weekly Mood Trend\n";
        cout << "\x1b[0m";
        cout << "0. Back\n";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: addMoodEntry(); break;
        case 2:
            clearScreen();
            printHeader("MOOD HISTORY");

            cout << "\x1b[36m";
            for (int i = moodCount - 1; i >= 0 && i >= moodCount - 7; i--) {
                cout << moods[i].date << " - " << moods[i].mood
                    << " (" << moods[i].score << "/5)\n";
                if (!moods[i].note.empty())
                    cout << "NOTE: " << moods[i].note << "\n";
                cout << endl;
            }
            cout << "\x1b[0m";
            pauseScreen();
            break;

        case 3: viewMoodTrend(); break;
        default: break;
        }
    } while (choice != 0);
}

// ==================== MODULE 5: ISLAMIC CONTENT ====================

void islamicMenu() {
    int choice;
    clearScreen();
    printHeader("ISLAMIC CONTENT");
    cout << "\x1b[91m";
    cout << "1. Verse of the Day\n";
    cout << "2. Dua of the Day\n";
    cout << "3. Simple Prayer Reminder\n";
    cout << "\x1b[0m";
    cout << "0. Back\n";
    cout << "\nChoice: ";
    cin >> choice;

    clearScreen();
     
    switch (choice) {
    case 1:
        printHeader("VERSE OF THE DAY");
        cout << "\x1b[91m";
        cout << islamicVerses[rand() % 5] << endl;
        cout << "\x1b[0m";
        break;
    case 2:
        printHeader("DUA OF THE DAY");
        cout << "\x1b[91m";
        cout << duas[rand() % 5] << endl;
        cout << "\x1b[0m";
        break;
    case 3:
        printHeader("PRAYER REMINDER");
        cout << "\x1b[91m";
        cout << "Remember the five daily prayers: Fajr, Dhuhr, Asr, Maghrib, Isha.\n";
        cout << "\x1b[3;91m";
        cout << "\nThe key to Paradise is prayer; the key to prayer is wudu (ablution)." << endl;
        cout << "\x1b[0m";
        break;
    default:
        break;
    }
    pauseScreen();
}

// ==================== MODULE 6: DAILY ROUTINE ====================

void dailyRoutineMenu() {
    clearScreen();
    printHeader("DAILY ROUTINE SUGGESTIONS");

    time_t now = time(0);
    tm* ltm = localtime(&now);
    int hour = ltm->tm_hour;

    cout << "\x1b[90m";
    cout << "SUGGESTIONS FOR TODAY:\n\n";

    if (hour >= 6 && hour <= 9) {
        cout << "- Morning: Have breakfast and drink water.\n";
    }
    else if (hour >= 12 && hour <= 14) {
        cout << "- Afternoon: Light walk if possible, and healthy lunch.\n";
    }
    else if (hour >= 20 && hour <= 23) {
        cout << "- Night: Prepare to sleep around " << user.sleepTime << ".\n";
    }

    if (healthCount > 0) {
        HealthReading latest = healthReadings[healthCount - 1];
        if (latest.systolic > 140)
            cout << "- Your BP was high recently. Avoid stress and salt.\n";
        if (latest.sugar > 180)
            cout << "- Your sugar was high. Limit sweets.\n";
    }

    if (moodCount > 0 && moods[moodCount - 1].score <= 2) {
        cout << "- Mood is low. Call family or listen to Quran.\n";
    }

    cout << "\nGENERAL TIPS:\n";
    cout << "- Take medicines on time.\n";
    cout << "- Drink enough water.\n";
    cout << "- Get some fresh air.\n";
    cout << "\x1b[0m";

    pauseScreen();
}

// ==================== MODULE 7: EMERGENCY CONTACTS ====================

void displayEmergencyContacts() {
    clearScreen();
    printHeader("EMERGENCY CONTACTS");

    if (contactCount == 0) {
        cout << "No contacts added.\n";
    }
    else {
        for (int i = 0; i < contactCount; i++) {
            cout << "--------------------------------------\n";
            cout << "\x1b[96m";
            cout << (i + 1) << ". " << contacts[i].name << endl << endl;
            cout << "Phone: " << contacts[i].phone << endl;
            cout << "Relation: " << contacts[i].relation << endl;
            cout << "\x1b[0m";
        }
    }
    pauseScreen();
}

void addEmergencyContact() {
    clearScreen();
    printHeader("ADD EMERGENCY CONTACT");

    if (contactCount >= 10) {
        cout << "Contact list is full.\n";
        pauseScreen();
        return;
    }

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "\x1b[96m";
    cout << "Name: ";
    cout << "\x1b[0m";

    getline(cin, contacts[contactCount].name);

    cout << "\x1b[96m";
    cout << "Phone number: ";
    cout << "\x1b[0m";

    getline(cin, contacts[contactCount].phone);

    cout << "\x1b[96m";
    cout << "Relation: ";
    cout << "\x1b[0m";

    getline(cin, contacts[contactCount].relation);

    contactCount++;
    saveContacts();

    cout << "\x1b[96m";
    cout << "\nContact added.\n";
    cout << "\x1b[0m";

    pauseScreen();
}

void emergencyMenu() {
    int choice;
    do {
        clearScreen();
        printHeader("EMERGENCY CONTACTS");
        cout << "\x1b[96m";
        cout << "1. View Contacts\n";
        cout << "2. Add Contact\n";
        cout << "3. Delete Contact\n";
        cout << "\x1b[0m";

        cout << "0. Back\n";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayEmergencyContacts();
            break;
        case 2:
            addEmergencyContact();
            break;
        case 3:
            if (contactCount == 0) {
                cout << "No contacts to delete.\n";
                pauseScreen();
            }
            else {
                displayEmergencyContacts();
                cout << "\x1b[96m";
                cout << "\nEnter contact number to delete (0 to cancel): ";
                cout << "\x1b[0m";

                int del;
                cin >> del;
                if (del > 0 && del <= contactCount) {
                    for (int i = del - 1; i < contactCount - 1; i++)
                        contacts[i] = contacts[i + 1];
                    contactCount--;
                    saveContacts();
                    cout << "\nContact deleted.\n";
                    pauseScreen();
                }
            }
            break;
        default:
            break;
        }
    } while (choice != 0);
}

// ==================== MODULE 8: INCIDENT LOG ====================

void logIncident() {
    clearScreen();
    printHeader("LOG INCIDENT");

    if (incidentCount >= 30) {
        cout << "Incident log is full.\n";
        pauseScreen();
        return;
    }

    incidents[incidentCount].date = getCurrentDate();

    cout << "\x1b[93m";
    cout << "Incident type:\n";
    cout << "1. Fall\n2. Pain\n3. Dizziness\n4. Confusion\n5. Panic\n\n";
    cout << "\x1b[0m";

    cout << "Choice: ";

    int type;
    cin >> type;
    cin.ignore();

    switch (type) {
    case 1: incidents[incidentCount].type = "Fall"; break;
    case 2: incidents[incidentCount].type = "Pain"; break;
    case 3: incidents[incidentCount].type = "Dizziness"; break;
    case 4: incidents[incidentCount].type = "Confusion"; break;
    case 5: incidents[incidentCount].type = "Panic"; break;
    default: incidents[incidentCount].type = "Other"; break;
    }

    cout << endl;
    cout << "\x1b[93m";
    cout << "Brief description: ";
    cout << "\x1b[0m";

    getline(cin, incidents[incidentCount].description);

    cout << "\x1b[93m";
    cout << "Severity (1-5): ";
    cout << "\x1b[0m";

    cin >> incidents[incidentCount].severity;

    incidentCount++;
    saveIncidents();

    cout << "\nIncident logged.\n";
    pauseScreen();
}

void viewIncidents() {
    clearScreen();
    printHeader("INCIDENT HISTORY");

    if (incidentCount == 0) {
        cout << "No incidents logged.\n";
    }
    else {
        for (int i = incidentCount - 1; i >= 0 && i >= incidentCount - 10; i--) {
            cout << "----------------------------------------\n";
            cout << "\x1b[93m";
            cout << "Date: " << incidents[i].date << endl << endl;
            cout << "Type: " << incidents[i].type << endl;
            cout << "Description: " << incidents[i].description << endl;
            cout << "Severity: " << incidents[i].severity << "/5\n";
            cout << "\x1b[0m";
        }
    }
    pauseScreen();
}

void incidentMenu() {
    int choice;
    do {
        clearScreen();
        printHeader("INCIDENT LOG");
        cout << "\x1b[93m";
        cout << "1. Log Incident\n";
        cout << "2. View History\n";
        cout << "\x1b[0m";

        cout << "0. Back\n";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: logIncident(); break;
        case 2: viewIncidents(); break;
        default: break;
        }
    } while (choice != 0);
}

// ==================== MODULE 9: SIMPLE GAMES ====================

void guessTheNumber() {
    clearScreen();
    printHeader("GUESS THE NUMBER");

    int secret = rand() % 100 + 1;
    int guess, attempts = 0;

    cout << "\x1b[94m";
    cout << "Guess a number between 1 and 100.\n\n";
    cout << "\x1b[0m";

    do {
        cout << "\x1b[94m";
        cout << "Your guess: " << "\x1b[0m";
        cin >> guess;
        attempts++;

        cout << "\x1b[94m";
        if (guess < secret)      cout << "Go Higher.\n\n";
        else if (guess > secret) cout << "Go Lower.\n\n";
        else                     cout << "\nCorrect in " << attempts << " attempts.\n";
        cout << "\x1b[0m";

    } while (guess != secret && attempts < 7);

    if (guess != secret)
        cout << "\x1b[94m" << "\nThe number was " << secret << ".\n" << "\x1b[0m";

    pauseScreen();
}

void quickMath() {
    clearScreen();
    printHeader("QUICK MATH");

    int score = 0;

    for (int i = 0; i < 5; i++) {
        int a = rand() % 20 + 1;
        int b = rand() % 20 + 1;
        int op = rand() % 2;
        int answer, correct;

        if (op == 0) {
            cout << "\x1b[94m";
            cout << "\nQuestion " << (i + 1) << ": " << "\x1b[0m";
            cout << a << " + " << b << " = ";

            correct = a + b;
        }
        else {
            if (a < b) swap(a, b);
            cout << "\x1b[94m";
            cout << "\nQuestion " << (i + 1) << ": " << "\x1b[0m";
            cout << a << " - " << b << " = ";

            correct = a - b;
        }

        cin >> answer;

        if (answer == correct) {
            cout << "\x1b[94m";
            cout << "CORRECT.\n";
            cout << "\x1b[0m";

            score++;
        }
        else {
            cout << "\x1b[94m";
            cout << "WRONG. Answer: " << "\x1b[0m" << correct << endl;
        }
    }

    cout << "\x1b[94m";
    cout << "\nScore: " << score << "/5\n";
    cout << "\x1b[0m";
    pauseScreen();
}

void gamesMenu() {
    int choice;
    do {
        clearScreen();
        printHeader("SIMPLE GAMES");
        cout << "\x1b[94m";
        cout << "1. Guess the Number\n";
        cout << "2. Quick Math\n";
        cout << "\x1b[0m";
        cout << "0. Back\n";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: guessTheNumber(); break;
        case 2: quickMath(); break;
        default: break;
        }
    } while (choice != 0);
}

// ==================== MODULE 10: SYMPTOM CHECKER ====================

void symptomChecker() {
    clearScreen();
    printHeader("SYMPTOM CHECKER");

    bool symptoms[6] = { false };

    cout << "\x1b[95m";
    cout << "Select symptoms:\n";
    cout << "1. Headache\n";
    cout << "2. Nausea\n";
    cout << "3. Dizziness\n";
    cout << "4. Chest pain\n";
    cout << "5. Fatigue\n\n";
    cout << "Enter numbers (1-5) to show what are you feeling. " << "\x1b[0m" << "(Enter 0 to finish) :";
   

    int s;
    while (true) {
        cin >> s;
        if (s == 0) break;
        if (s >= 1 && s <= 5) symptoms[s] = true;
    }

    clearScreen();
    printHeader("SYMPTOM ANALYSIS");

    if (symptoms[4] && symptoms[5]) {

        cout << "\x1b[95m";
        cout << "Chest pain with fatigue. Seek immediate medical attention.\n";
        cout << "\x1b[0m";
        displayEmergencyContacts();
        pauseScreen();
        return;
    }

    if (symptoms[1] && symptoms[3]) {
        cout << "\x1b[95m";
        cout << "Headache with dizziness. Check BP and rest.\n";
        cout << "\x1b[0m";
    }
    else if (symptoms[5] && healthCount > 0 &&
        healthReadings[healthCount - 1].sugar > 160) {
        cout << "\x1b[95m";
        cout << "Fatigue with high sugar. Monitor sugar and avoid sweets.\n";
        cout << "\x1b[0m";
    }
    else if (symptoms[2] && symptoms[3]) {
        cout << "\x1b[95m";
        cout << "Nausea with dizziness. Rest and stay hydrated.\n";
        cout << "\x1b[0m";
    }
    else {
        cout << "\x1b[95m";
        cout << "Mild symptoms. Rest, hydrate, and monitor.\n";
        cout << "\x1b[0m";
    }

    pauseScreen();
}

// ==================== MODULE 11: CAREGIVER MODE ====================

void caregiverWeeklySummary() {
    clearScreen();
    printHeader("WEEKLY SUMMARY FOR CAREGIVER");

    cout << "\x1b[92m";
    cout << "Patient: " << "\x1b[0m" << user.name << " (" << user.age << " years)\n";

    cout << "\x1b[92m";
    cout << "\nMedicine adherence today:\n";
    cout << "\x1b[0m";

    int taken = 0;
    for (int i = 0; i < medicineCount; i++)
        if (medicines[i].takenToday) taken++;
    if (medicineCount > 0)
        cout << "Taken " << taken << " of " << medicineCount << ".\n";
    else
        cout << "No medicines defined.\n";

    cout << "\x1b[92m";
    cout << "\nLATEST HEALTH READINGS:\n";
    cout << "\x1b[0m";

    if (healthCount > 0) {
        HealthReading latest = healthReadings[healthCount - 1];

        cout << "\x1b[92m" << "BP: " << "\x1b[0m" << latest.systolic << "/" << latest.diastolic << "\n";
        cout << "\x1b[92m" << "Sugar: " << "\x1b[0m" << latest.sugar << " mg/dL\n";
        cout << "\x1b[92m" << "Heart rate: " << "\x1b[0m" << latest.heartRate << " bpm\n";
    }
    else {
        cout << "No readings.\n";
    }

    cout << "\x1b[92m";
    cout << "\nMOOD (last week):\n";
    cout << "\x1b[0m";

    if (moodCount > 0) {
        float avg = 0.0f;
        int count = (moodCount < 7) ? moodCount : 7;
        for (int i = moodCount - 1; i >= moodCount - count; i--)
            avg += moods[i].score;
        avg /= count;
        cout << "\x1b[92m" << "Average mood score: " << "\x1b[0m" << fixed << setprecision(1)
            << avg << "/5\n";
    }
    else {
        cout << "No mood entries.\n";
    }

    cout << "\x1b[92m" << "\nIncidents recorded: " << "\x1b[0m" << incidentCount << "\n";
    pauseScreen();
}

void caregiverMenu() {
    clearScreen();
    printHeader("CAREGIVER MODE");

    cout << "\x1b[92m";
    cout << "Enter PIN: ";
    cout << "\x1b[0m";

    string pin;
    cin >> pin;

    if (pin != CAREGIVER_PIN) {
        cout << "\nAccess denied.\n";
        pauseScreen();
        return;
    }

    int choice;
    do {
        clearScreen();
        printHeader("CAREGIVER MENU");
        cout << "\x1b[92m";
        cout << "1. Weekly Summary\n";
        cout << "2. Medicine Adherence\n";
        cout << "3. Mood Trend\n";
        cout << "4. Health Average\n";
        cout << "5. Incident History\n";
        cout << "6. Manage Medicines\n";
        cout << "7. Manage Emergency Contacts\n";
        cout << "\x1b[0m";

        cout << "0. Exit Caregiver Mode\n";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: caregiverWeeklySummary(); break;
        case 2: weeklyAdherenceReport(); break;
        case 3: viewMoodTrend(); break;
        case 4: weeklyHealthAverage(); break;
        case 5: viewIncidents(); break;
        case 6: medicineMenu(); break;
        case 7: emergencyMenu(); break;
        default: break;
        }
    } while (choice != 0);
}

// ==================== MAIN MENU ====================

void displayWelcome() {
    clearScreen();
    printHeader("ELDER CARE DIGITAL ASSISTANT");
    

    if (!user.name.empty()) {
        cout << "Welcome, " << user.name << ". Today is "
            << getCurrentDate() << " " << getCurrentTime() << "\n";
        cout << endl;
        checkMedicineReminders();
    }
}

void mainMenu() {
    int choice;
    do {
        displayWelcome();

        cout << "\n==( MAIN MENU )==\n\n";
        cout << "\x1b[32m";
        cout << "1. Profile\n"; //green
        cout << "\x1b[35m";
        cout << "2. Medicine Reminders\n"; //magenta
        cout << "\x1b[33m";
        cout << "3. Health Tracker\n";
        cout << "\x1b[36m";
        cout << "4. Mood and Journal\n";
        cout << "\x1b[91m";
        cout << "5. Islamic Content\n";
        cout << "\x1b[90m";
        cout << "6. Daily Routine\n";
        cout << "\x1b[96m";        
        cout << "7. Emergency Contacts\n";
        cout << "\x1b[93m";
        cout << "8. Incident Log\n";
        cout << "\x1b[94m";
        cout << "9. Simple Games\n";
        cout << "\x1b[95m";
        cout << "10. Symptom Checker\n";
        cout << "\x1b[92m";
        cout << "11. Caregiver Mode\n";
        cout << "\x1b[0m";
        cout << "0. Exit\n";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: profileMenu(); break;
        case 2: medicineMenu(); break;
        case 3: healthMenu(); break;
        case 4: moodMenu(); break;
        case 5: islamicMenu(); break;
        case 6: dailyRoutineMenu(); break;
        case 7: emergencyMenu(); break;
        case 8: incidentMenu(); break;
        case 9: gamesMenu(); break;
        case 10: symptomChecker(); break;
        case 11: caregiverMenu(); break;
        case 0:
            cout << "\nSaving data...\n";
            saveAllData();
            cout << "Goodbye.\n";
            break;
        default:
            cout << "\nInvalid choice.\n";
            pauseScreen();
        }
    } while (choice != 0);
}