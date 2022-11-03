#include <iostream>
#include <string>
#include <fstream>
using namespace std;


class HospitalCommands {
    string firstName;
    string middleName;
    string lastName;
    string suffix;
    string ailment;
    string doctorName;
    string isTreated;
    string priority;


public:
    HospitalCommands(string newFirstName, string newMiddleName, string newLastName, string newSuffix,
                     string newAilment, string newDoctorName,
                     string newIsTreated, string newPriority);

    void printReport();

    int returnPriorityNumber();

    int returnTreatedNumber();

    string returnFirstName();

    string returnMiddleName();

    string returnLastName();

    string returnDoctorName();


};

