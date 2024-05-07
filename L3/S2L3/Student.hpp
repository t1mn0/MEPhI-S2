#include "Person.hpp"
#include "String.hpp"

class Student : public Person {
private:
    PersonID id;
    String firstName;
    String middleName;
    String lastName;
    String bday;
    String universityName;
    int yearOfStudy;

public:
    Student(const String& firstName, const String& middleName, const String& lastName,
        const String& birthDate, const String& universityName, int yearOfStudy)
        : Person(firstName, middleName, lastName, birthDate),
        universityName(universityName), yearOfStudy(yearOfStudy) { id = PersonID(); }

    void printInfo() const override {
        std::cout << "ID: " << id.getID();
        std::cout << " FirstName: ";
        for (int i = 0; i < firstName.size(); ++i) {
            std::cout << firstName[i];
        }
        std::cout << " MiddleName: ";
        for (int i = 0; i < middleName.size(); ++i) {
            std::cout << middleName[i];
        }
        std::cout << " LastName: ";
        for (int i = 0; i < lastName.size(); ++i) {
            std::cout << lastName[i];
        }
        std::cout << " Birthday: ";
        for (int i = 0; i < bday.size(); ++i) {
            std::cout << bday[i];
        }

        std::cout << " Current position: Student";
        std::cout << " University name: ";
        for (int i = 0; i < universityName.size(); ++i) {
            std::cout << universityName[i];
        }
        std::cout << "Time at university: " << yearOfStudy ;
    }
};