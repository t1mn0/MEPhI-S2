#pragma once

#include "Person.hpp"


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
    Student()
        : Person(String("a"), String("a"), String("a"), String("01-01-2001")), id(), universityName("a"), yearOfStudy(0){}

    Student(const String& firstName, const String& middleName, const String& lastName,
        const String& bday, const String& universityName, int yearOfStudy)
        : Person(firstName, middleName, lastName, bday),
        universityName(universityName), yearOfStudy(yearOfStudy) { 
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

    int getYearsOfStudy() const {
        return yearOfStudy;
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
        std::cout << "\n | Current position: Student\n";
        std::cout << " | University name: ";
        for (int i = 0; i < universityName.size(); ++i) {
            std::cout << universityName[i];
        }
        std::cout << "\n | Time of study at university: " << yearOfStudy;
        std::cout << "\n |__________________________________\n";
    }

    bool operator==(const Student& other) const {
        if (this->firstName != other.firstName) return false;
        if (this->middleName != other.middleName) return false;
        if (this->lastName != other.lastName) return false;
        if (this->bday != other.bday) return false;
        return this->universityName == other.universityName && this->yearOfStudy == other.yearOfStudy;
    }

    bool operator!=(const Student& other) const {
        return !(*this == other);
    }

};
