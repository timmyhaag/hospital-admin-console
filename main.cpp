#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <chrono>
#include <thread>
using namespace std;
using namespace this_thread;
using namespace chrono;
#include "HospitalCommands.h"


int main() {
    string firstName;
    string middleName;
    string lastName;
    string suffix;
    string ailment;
    string ailment2;
    string doctorName;
    string isTreated;
    string priority;
    string tempString;

    string userInput;
    int commandNum = 0;
    string commandString;

    int index = 0;
    vector<HospitalCommands> hsVector;
    vector<HospitalCommands> treatedVector;
    vector<string> vectorDoctorNames;
    priority_queue<int, vector<int>, greater<int>> pq;

    ifstream inFile;
    ofstream outFile;
    bool validInput = false;
    bool debugOn = false;

    do {
        try {
        cout << "Hospital Emergency Room Triage" << endl;
        cout << "The following commands below may be performed: "
                " \n"
                "(1) Add a patient to the system \n"
                "(2) Treat a patient in triaged order \n"
                "(3) Print out a patients information as a report \n"
                "(4) Print out a report of all treated patients \n"
                "(5) Search the next patient to be treated \n"
                "(6) Print out a report of all the patients in triage \n"
                "(7) Treat all patients \n"
                "(8) Create print out of all patients by doctor \n"
                "(9) Print out a guide on each command the system offers \n"
                "(10) Bulk add patients into the system from a file \n"
                "(11) Enforce all operations of the system by each user to be logged to a file in normal mode \n"
                "(12) Turn on debug mode. "
                "Enforce all operations of the system by each user to be logged to the console in debug mode \n\n"
                "Enter the number of the command that you would like to perform: " << endl;

        cin >> userInput;

        if (userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4" &&
            userInput != "5" && userInput != "6" && userInput != "7" && userInput != "8" &&
            userInput != "9" && userInput != "10" && userInput != "11" && userInput != "12") {
            throw exception();
        }
        cout << "\n" << endl;
        commandNum = stoi(userInput);
        }
        catch (...) {
            cout << "\nPlease only input a number with no spaces for the command you want to use\n" << endl;
            continue;
        }

        switch (commandNum) {
            case 1: {
                if (outFile.is_open()) {
                    outFile << "Command entered:\n(1) Add a patient to the system\n";
                    outFile.flush();
                }

                if (debugOn) {
                    cout << "Command entered:\n(1) Add a patient to the system\n" << endl;

                }

                try {
                    string tempAilment = "Ailment: ";
                    cin.ignore();
                    cout << "Enter first name: " << endl;
                    getline(cin, firstName, '\n');

                    cout << "Enter middle name: " << endl;
                    getline(cin, middleName, '\n');

                    cout << "Enter last name: " << endl;
                    getline(cin, lastName, '\n');

                    cout << "Enter suffix: " << endl;
                    getline(cin, suffix, '\n');

                    cout << "Enter all ailments: " << endl;
                    cin.ignore();
                    getline(cin, ailment, '\n');
                    tempAilment += ailment;

                    cout << "Enter doctor name: " << endl;
                    getline(cin, doctorName, '\n');

                    cout << "Enter treated status (0 or 1): " << endl;
                    getline(cin, isTreated, '\n');

                    cout << "Enter priority number: " << endl;
                    getline(cin, priority, '\n');

                    HospitalCommands tempHS(firstName, middleName, lastName, suffix,
                                            tempAilment, doctorName, isTreated,
                                            priority);

                    if (tempHS.returnTreatedNumber() != 0 && tempHS.returnTreatedNumber() != 1) {
                        throw exception();
                    }

                    if (isTreated.length() > 1) {
                        throw exception();
                    }

                    if (tempHS.returnPriorityNumber() < 0) {
                        throw exception();
                    }

                    if (priority == "-0") {
                        throw exception();
                    }

                    for (int i = 0; i < priority.length(); i++) {
                        if (isspace(priority.at(i))) {
                            throw exception();
                        }
                    }

                    cout << "\nAdded patient: \n" << endl;

                    if (tempHS.returnTreatedNumber() == 0) {
                        hsVector.push_back(tempHS);
                        hsVector.back().printReport();
                        pq.push(hsVector.back().returnPriorityNumber());
                    } else {
                        treatedVector.push_back(tempHS);
                        treatedVector.back().printReport();
                    }

                    if (!vectorDoctorNames.empty()) {
                        if (find(vectorDoctorNames.begin(), vectorDoctorNames.end(), doctorName) !=
                            vectorDoctorNames.end()) {
                            break;
                        } else {
                            vectorDoctorNames.push_back(doctorName);
                        }
                    } else {
                        vectorDoctorNames.push_back(doctorName);
                    }
                }
                catch(...) {
                    cout << "\nPlease only input the appropriate response for the first name, middle name,"
                            " last name, suffix,"
                            " and doctor name. Treated status must be a number that's either"
                            " 0 or 1 with no spaces. Priority must be a number that is"
                            " 0 or more with no spaces.\n" << endl;
                }

                break;
            }

            case 2: {
                if (outFile.is_open()) {
                    outFile << "Command entered:\n(2) Treat a patient in triaged order\n";
                    outFile.flush();
                }

                if (debugOn) {
                    cout << "Command entered:\n(2) Treat a patient in triaged order\n" << endl;

                }

                try {
                    if (!hsVector.empty()) {
                        int highestPriority = pq.top();

                        for (int i = 0; i < hsVector.size(); i++) {
                            if (hsVector.at(i).returnPriorityNumber() == highestPriority) {
                                HospitalCommands tempHS = hsVector.at(i);
                                treatedVector.push_back(tempHS);
                                hsVector.erase(hsVector.begin() + i);
                                pq.pop();
                                int num = rand() % 3 + 1;
                                sleep_for(seconds (num));
                                cout << hsVector.at(i).returnFirstName() + " " +
                                        hsVector.at(i).returnLastName() + " has been treated.\n" << endl;
                                break;
                            }
                        }
                    } else {
                        cout << "No patients to treat\n" << endl;
                    }
                }

                catch (...) {
                    cout << "\nError occurred. \n" << endl;
                }

                break;
            }

            case 3: {
                if (outFile.is_open()) {
                    outFile << "Command entered:\n(3) Print out a patients information as a report\n";
                    outFile.flush();
                }

                if (debugOn) {
                    cout << "Command entered:\n(3) Print out a patients information as a report\n" << endl;

                }

                try {
                    string tempFirstName;
                    string tempMiddleName;
                    string tempLastName;
                    string tempPriorityString;
                    int tempPriorityNum;

                    cout << "**Input is case sensitive**" << endl;
                    cout << "Enter patients first name: " << endl;

                    cin.ignore();
                    getline(cin, tempFirstName, '\n');

                    cout << "Enter patients middle name: " << endl;
                    getline(cin, tempMiddleName, '\n');

                    cout << "Enter patients last name: " << endl;
                    getline(cin, tempLastName, '\n');

                    cout << "Enter patients priority number: " << endl;
                    getline(cin, tempPriorityString, '\n');
                    tempPriorityNum = stoi(tempPriorityString);
                    cout << "\n" << endl;

                    for (int i = 0; i < hsVector.size(); i++) {
                        if ((hsVector.at(i).returnFirstName() == tempFirstName) &&
                            (hsVector.at(i).returnMiddleName() == tempMiddleName) &&
                            (hsVector.at(i).returnLastName() == tempLastName) &&
                            (hsVector.at(i).returnPriorityNumber() == tempPriorityNum)) {

                            hsVector.at(i).printReport();
                            break;
                        }
                        else if (i == (hsVector.size() - 1)){
                            cout << "No report found in the list of patients waiting to"
                                    " be treated.\n" << endl;
                        }
                    }

                    for (int i = 0; i < treatedVector.size(); i++) {
                        if ((treatedVector.at(i).returnFirstName() == tempFirstName) &&
                            (treatedVector.at(i).returnMiddleName() == tempMiddleName) &&
                            (treatedVector.at(i).returnLastName() == tempLastName) &&
                            (treatedVector.at(i).returnPriorityNumber() == tempPriorityNum)) {

                            treatedVector.at(i).printReport();
                            break;
                        }

                        else if (i == (treatedVector.size() - 1)) {
                            cout << "\nNo report found in the list of patients who have been"
                                    " treated.\n" << endl;
                        }
                    }
                }

                catch (...) {
                    cout << "\nError occurred. Make sure inputted information is correct and formatted"
                            " properly.\n" << endl;
                }

                break;
            }

            case 4: {
                if (outFile.is_open()) {
                    outFile << "Command entered:\n(4) Print out a report of all treated patients\n";
                    outFile.flush();
                }

                if (debugOn) {
                    cout << "Command entered:\n(4) Print out a report of all treated patients\n" << endl;

                }

                try {
                    cout << "All patients that have been treated: \n" << endl;
                    if (!treatedVector.empty()) {
                        for (int i = 0; i < treatedVector.size(); i++) {
                            treatedVector.at(i).printReport();
                        }
                    }
                    else {
                        cout << "No treated patients found\n" << endl;
                    }
                }

                catch (...) {
                    cout << "\nAn error has occurred.\n" << endl;
                }

                break;
            }

            case 5: {
                if (outFile.is_open()) {
                    outFile << "Command entered:\n(5) Search the next patient to be treated\n";
                    outFile.flush();
                }

                if (debugOn) {
                    cout << "Command entered:\n(5) Search the next patient to be treated\n" << endl;

                }

                try {
                    if (!hsVector.empty()) {
                        int highestPriority = pq.top();

                        for (int i = 0; i < hsVector.size(); i++) {
                            if (hsVector.at(i).returnPriorityNumber() == highestPriority) {
                                cout << "Next patient to be treated: \n" << endl;
                                hsVector.at(i).printReport();
                                break;
                            }
                        }
                    }
                    else {
                        cout << "No patients in queue to be treated\n" << endl;
                    }
                }

                catch (...) {
                    cout << "\nAn error has occurred.\n" << endl;
                }


                break;
            }

            case 6: {
                if (outFile.is_open()) {
                    outFile << "Command entered:\n(6) Print out a report of all the patients in triage\n";
                    outFile.flush();
                }

                if (debugOn) {
                    cout << "Command entered:\n(6) Print out a report of all the patients in triage\n" << endl;

                }

                try {
                    cout << "All patients waiting to be treated: \n" << endl;
                    if (!hsVector.empty()) {
                        for (int i = 0; i < hsVector.size(); i++) {
                            hsVector.at(i).printReport();
                        }
                    } else {
                        cout << "No patients in queue to be treated\n" << endl;
                    }
                }

                catch (...) {
                    cout << "\nAn error has occurred.\n" << endl;
                }

                break;
            }

            case 7: {
                if (outFile.is_open()) {
                    outFile << "Command entered:\n(7) Treat all patients\n";
                    outFile.flush();
                }

                if (debugOn) {
                    cout << "Command entered:\n(7) Treat all patients\n" << endl;

                }

                try {
                    if (!hsVector.empty()) {
                        while (!hsVector.empty()) {
                            for (int i = 0; i < hsVector.size(); i++) {
                                int highestPriority = pq.top();
                                if (hsVector.at(i).returnPriorityNumber() == highestPriority) {
                                    HospitalCommands tempHS = hsVector.at(i);
                                    treatedVector.push_back(tempHS);
                                    hsVector.erase(hsVector.begin() + i);
                                    pq.pop();
                                    int num = rand() % 3 + 1;
                                    sleep_for(seconds (num));
                                    cout << "Treated patient:\n" << endl;
                                    treatedVector.back().printReport();
                                    break;
                                }

                            }
                        }
                    }
                    else {
                        cout << "No patients to treat\n" << endl;
                    }
                }

                catch (...) {
                    cout << "\nAn error has occurred.\n" << endl;
                }

                break;
            }

            case 8: {
                if (outFile.is_open()) {
                    outFile << "Command entered:\n(8) Create print out of all patients by doctor\n";
                    outFile.flush();
                }

                if (debugOn) {
                    cout << "Command entered:\n(8) Create print out of all patients by doctor\n" << endl;

                }

                try {
                    if (!hsVector.empty() || !treatedVector.empty()) {
                        for (int i = 0; i < vectorDoctorNames.size(); i++) {
                            cout << "All patients listed under " + vectorDoctorNames.at(i) + ":\n" << endl;
                            for (int j = 0; j < hsVector.size(); j++) {
                                if (hsVector.at(j).returnDoctorName() == vectorDoctorNames.at(i)) {
                                    hsVector.at(j).printReport();
                                }
                            }

                            for (int k = 0; k < treatedVector.size(); k++) {
                                if (treatedVector.at(k).returnDoctorName() == vectorDoctorNames.at(i)) {
                                    treatedVector.at(k).printReport();
                                }
                            }
                        }

                    }
                    else {
                        cout << "No patients or doctors on record\n" << endl;
                    }
                }

                catch (...) {
                    cout << "\nAn error has occurred.\n" << endl;
                }

                break;
            }

            case 9: {
                if (outFile.is_open()) {
                    outFile << "Command entered:\n(9) Print out a guide on each command the system offers\n";
                    outFile.flush();
                }

                if (debugOn) {
                    cout << "Command entered:\n(9) Print out a guide on each command the system offers\n" << endl;

                }

                try {

                    cout << "Guide to commands" << endl;
                    cout << "(1) Add a patient to the system \n"
                            "- Add a patient and their correlating information into the list of patients waiting"
                            " to be treated. Info will include \ntheir first name, middle name, last name, suffix,"
                            " ailments, doctor name, treatment status(0 or 1), and priority number.\n"
                            "(2) Treat a patient in triaged order \n- Automatically treat a patient with the highest priority"
                            " and move their personal report to a list of patients who have been treated.\n"
                            "(3) Print out a patients information as a report \n- The user will enter a patients"
                            " first name, middle name, last name, and priority number. A report of that patients \ninformation "
                            "will then be printed out.\n"
                            "(4) Print out a report of all treated patients \n- Automatically print out a report of every patient"
                            " that has been treated.\n"
                            "(5) Search the next patient to be treated \n- A search will be made for the patient that"
                            " has the highest priority and is queued to be treated next. Once found, the patients"
                            " report will be printed.\n"
                            "(6) Print out a report of all the patients in triage \n- Automatically "
                            "print out a report of every patient waiting to be treated.\n"
                            "(7) Treat all patients \n- Automatically treat each patient"
                            " in triaged order, remove them from the list of patients waiting to be treated, "
                            "and \nadd each patient to the list of patients who have been treated.\n"
                            "(8) Create print out of all patients by doctor \n- For each doctor listed"
                            ", a report will be printed out of every patient listed under the corresponding doctor."
                            "These \npatients includes those waiting to be treated and patients that have been treated\n"
                            "(9) Print out a guide on each command the system offers \n- A guide will be printed that gives "
                            "additional information on each command.\n"
                            "(10) Bulk add patients into the system from a file \n- Adds all patients information"
                            " from a file into the list of patients waiting to be treated.\n"
                            "(11) Enforce all operations of the system by each user to be logged to a file in normal mode \n"
                            "- Every command that a user enters will be inputted to a file to log the history of commands by users.\n"
                            "(12) Turn on debug mode. "
                            "Enforce all operations of the system by each user to be logged to the console in debug mode \n"
                            "- Every command that a user enters will be printed to the console as each command is used.\n\n"
                            "Enter the number of the command that you would like to perform: " << endl;
                }

                catch (...) {
                    cout << "\nAn error has occured.\n" << endl;
                }


                break;
            }

            case 10: {
                if (outFile.is_open()) {
                    outFile << "Command entered:\n(10) Bulk add patients into the system from a file\n";
                    outFile.flush();
                }
                if (debugOn) {
                    cout << "Command entered:\n(10) Bulk add patients into the system from a file\n" << endl;

                }

                try {
                    if (!inFile.is_open()) {
                        string fileName;
                        cout << "Enter the name of the file that you want to use to import patient data ("
                                "You may need to enter the absolute path of \nthe file itself): " << endl;
                        cin.ignore();
                        getline(cin, fileName);
                        inFile.open(fileName);

                        while (!validInput) {
                            getline(inFile, firstName, ':');
                            getline(inFile, firstName, '\n');

                            getline(inFile, middleName, ':');
                            getline(inFile, middleName, '\n');

                            getline(inFile, lastName, ':');
                            getline(inFile, lastName, '\n');

                            getline(inFile, suffix, ':');
                            getline(inFile, suffix, '\n');

                            string tempAilment;
                            while (getline(inFile, tempString, ':') && (tempString == "ailment")) {
                                getline(inFile, ailment, '\n');
                                tempAilment += "Ailment: " + ailment + "\n";
                            }

                            tempAilment += "Ailment: n/a";
                            getline(inFile, doctorName, '\n');

                            getline(inFile, isTreated, ':');
                            getline(inFile, isTreated, '\n');

                            getline(inFile, priority, ':');
                            getline(inFile, priority, '\n');

                            getline(inFile, tempString, '\n');

                            index++;
                            HospitalCommands tempHS(firstName, middleName, lastName, suffix,
                                                    tempAilment, doctorName, isTreated,
                                                    priority);

                            bool yes = false;
                            if (tempHS.returnTreatedNumber() == 1) {
                                yes = true;
                            }

                            if (tempHS.returnTreatedNumber() != 0 && tempHS.returnTreatedNumber() != 1) {
                                throw exception();
                            }

                            if (isTreated.length() > 1) {
                                throw exception();
                            }

                            if (tempHS.returnPriorityNumber() < 0) {
                                throw exception();
                            }

                            for (int i = 0; i < priority.length(); i++) {
                                if (isspace(priority.at(i))) {
                                    throw exception();
                                }
                            }

                            if (yes) {
                                treatedVector.push_back(tempHS);
                                treatedVector.back().printReport();
                            } else {
                                hsVector.push_back(tempHS);
                                hsVector.back().printReport();
                                pq.push(hsVector.back().returnPriorityNumber());
                            }

                            if (!vectorDoctorNames.empty()) {
                                if (find(vectorDoctorNames.begin(), vectorDoctorNames.end(), doctorName) !=
                                    vectorDoctorNames.end()) {
                                    break;
                                } else {
                                    vectorDoctorNames.push_back(doctorName);
                                }
                            } else {
                                vectorDoctorNames.push_back(doctorName);
                            }

                            if (inFile.eof()) {
                                cout << "EOF\n" << endl;
                                validInput = true;
                            } else if (inFile.fail()) {
                                inFile.clear();
                            }
                        }
                    }

                    else {
                        cout << "A file has already been opened\n" << endl;
                    }

                    inFile.close();
                    inFile.clear();
                }

                catch (...) {
                    cout << "\nPlease ensure the file has an appropriate response for the "
                            "first name, middle name,"
                            " last name, suffix,"
                            " and doctor name. Treated status must be a number that's either"
                            " 0 or 1 with no spaces. Priority must be a number that is"
                            " 0 or more with no spaces.\n" << endl;
                }

                break;
            }

            case 11: {
                if (!outFile.is_open()) {
                    outFile.open("outputFile.txt");
                    cout << "Each command is now being logged to outputFile.txt\n" << endl;
                }

                if (outFile.is_open()) {
                    outFile << "Command entered:\n(11) Enforce all operations of the system by each"
                               " user to be logged to a file in normal mode\n";
                    outFile.flush();

                }

                if (debugOn) {
                    cout << "Command entered:\n(11) Enforce all operations of the system by each"
                            " user to be logged to a file in normal mode\n" << endl;

                }

                break;
            }

            case 12: {
                debugOn = true;

                if (outFile.is_open()) {
                    outFile << "Command entered:\n(12) Turn on debug mode. "
                               "Enforce all operations of the system by each user to be "
                               "logged to the console in debug mode \n";
                    outFile.flush();

                }

                if (debugOn) {
                    cout << "Command entered:\n(12) Turn on debug mode. "
                            "Enforce all operations of the system by each user to be logged to the console in debug mode \n"
                         << endl;

                }
                break;
            }

            default:
                break;
        }
    } while (true);

    inFile.close();
    outFile.close();
    return 0;
}
