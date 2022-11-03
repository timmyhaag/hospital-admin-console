#include "HospitalCommands.h"


HospitalCommands::HospitalCommands(string newFirstName, string newMiddleName,
                                   string newLastName, string newSuffix,
                                   string newAilment, string newDoctorName,
                                   string newIsTreated, string newPriority) {
    firstName = newFirstName;
    middleName = newMiddleName;
    lastName = newLastName;
    suffix = newSuffix;
    ailment = newAilment;
    doctorName = newDoctorName;
    isTreated = newIsTreated;
    priority = newPriority;

}

void HospitalCommands::printReport() {
    cout << "First Name: " + firstName<< endl;
    cout << "Middle Name: " + middleName<< endl;
    cout << "Last Name: " + lastName<< endl;
    if (suffix.empty()) {
        cout << "Suffix: n/a" + suffix<< endl;
    }
    else {
        cout << "Suffix: " + suffix<< endl;
    }
    cout << ailment<< endl;
    cout << "Doctor Name: " + doctorName<< endl;
    cout << "Treated Status: " + isTreated<< endl;
    cout << "Priority Number: " + priority + "\n"<< endl;
}

int HospitalCommands::returnPriorityNumber() {
    int priorityNumber = stoi(priority);
    return priorityNumber;
}

string HospitalCommands::returnFirstName() {
    return firstName;
}

string HospitalCommands::returnMiddleName() {
    return middleName;
}

string HospitalCommands::returnLastName() {
    return lastName;
}

string HospitalCommands::returnDoctorName() {
    return doctorName;
}

int HospitalCommands::returnTreatedNumber() {
    int treatedNumber = stoi(isTreated);
    return treatedNumber;
}


