#pragma once

#include "Person.hpp"

class Teacher : public Person {
private:
    PersonID id;
    String firstName;
    String middleName;
    String lastName;
    String bday;
    String universityName;
    int yearOfWork;

public:
    Teacher()
        : Person(String("a"), String("a"), String("a"), String("01-01-2001")), id(), universityName("a"), yearOfWork(0) {}

    Teacher(const String& firstName, const String& middleName, const String& lastName,
        const String& bday, const String& universityName, int yearOfWork)
        : Person(firstName, middleName, lastName, bday),
        universityName(universityName), yearOfWork(yearOfWork) {
        if (isValidName(firstName)) {
            this->firstName = firstName;
        }
        else {
            throw Exception(ErrorCode::invalid_argument);
        }
        if (isValidName(middleName)) {
            this->middleName = middleName;
        }
        else {
            throw Exception(ErrorCode::invalid_argument);
        }
        if (isValidName(lastName)) {
            this->lastName = lastName;
        }
        else {
            throw Exception(ErrorCode::invalid_argument);
        }
        if (isValidDate(bday)) {
            this->bday = bday;
        }
        else {
            throw Exception(ErrorCode::invalid_argument);
        }
    }

    int getYearsOfWork() const {
        return yearOfWork;
    }

    String getNameOfUniversity() const {
        return universityName;
    }

    void printInfo() const override {
        std::cout << "\n |----------------------------------\n";
        std::cout << " | ID: " << id.getID() << '\n';
        std::cout << " | FirstName: ";
        for (int i = 0; i < firstName.size(); ++i) {
            std::cout << firstName[i];
        }
        std::cout << "\n | MiddleName: ";
        for (int i = 0; i < middleName.size(); ++i) {
            std::cout << middleName[i];
        }
        std::cout << "\n | LastName: ";
        for (int i = 0; i < lastName.size(); ++i) {
            std::cout << lastName[i];
        }
        std::cout << "\n | Birthday: ";
        for (int i = 0; i < bday.size(); ++i) {
            std::cout << bday[i];
        }
        std::cout << "\n | Current position: Teacher\n";
        std::cout << " | University name: ";
        for (int i = 0; i < universityName.size(); ++i) {
            std::cout << universityName[i];
        }
        std::cout << "\n | Time of work at university: " << yearOfWork;
        std::cout << "\n |__________________________________\n";
    }

    bool operator==(const Teacher& other) const {
        if (this->firstName != other.firstName) return false;
        if (this->middleName != other.middleName) return false;
        if (this->lastName != other.lastName) return false;
        if (this->bday != other.bday) return false;
        return this->universityName == other.universityName && this->yearOfWork == other.yearOfWork;
    }

    bool operator!=(const Teacher& other) const {
        return !(*this == other);
    }
};
