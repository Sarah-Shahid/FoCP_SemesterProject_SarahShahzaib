#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<iomanip>

using namespace std;

struct UserProfile {

    string name;
    int age;
    string gender;
    string bloodgroup;
    bool profileExists;

};

struct Medicine {

    int medicineID;
    string name;
    string dosage;
    string frequency;

};

struct Appointments {

    int appointmentID;
    string date;
    string time;
    string doctorName;
    bool completed;

};

struct HealthReadings {

    string date;
    string time;
    int systolic;
    int diastolic;
    int heartrate;
    int sugarlevel;
    double weight;

};

struct Mood_Journaling {

    string date;
    string time;
    string mood;
    string journal_notes;

};

struct EmergencyContacts {

    string name;
    long long int phone_number;
    string relation;

};

struct IslamicSection {

    string verse;
    string dua;
    
};

struct IncidentLog {

    string date;
    string time;
    string incidentType;
    string description;

};


int main(){

    return 0;
}