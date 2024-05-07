#pragma once
#include <iostream>
#include "String.hpp"
#include "_StringUtilitie_.hpp"

class PersonID {
private:
    static int nextID;
    int id;

public:
    PersonID() : id(nextID++) {}

    int getID() const{
        return id;
    }
};

int PersonID::nextID = 1;

class Person {
private:
    PersonID id;
    String firstName;
    String middleName;
    String lastName;
    String bday;

public:
    Person(const String& firstName, const String& middleName, const String& lastName, const String& bday) {
        if (isValidName(firstName)) {
            this->firstName = firstName;
        }
        if (isValidName(middleName)) {
            this->middleName = middleName;
        }
        if (isValidName(lastName)) {
            this->lastName = lastName;
        }
        if (isValidDate(bday)) {
            this->bday = bday;
        }
        id = PersonID();
    }

    virtual ~Person() {}

    PersonID getID() const { return id; }
    String getFirstName() const { return firstName; }
    String getMiddleName() const { return middleName; }
    String getLastName() const { return lastName; }
    String getFullName() const {
        String fullname = firstName;
        fullname.push_back(' ');
        fullname.push_back(middleName);
        fullname.push_back(' ');
        fullname.push_back(lastName);
        return fullname;
    }
    String getBirthDate() const { return bday; }

    void setFirstName(const String& newFirstName) {
        if (isValidName(newFirstName)) {
            firstName = newFirstName;
        }
        else {
            throw Exception(ErrorCode::invalid_argument);
        }
    }
    void setMiddleName(const String& newMiddleName) {
        if (isValidName(newMiddleName)) {
            middleName = newMiddleName;
        }
        else {
            throw Exception(ErrorCode::invalid_argument);
        }
    }
    void setLastName(const String& newLastName) {
        if (isValidName(newLastName)) {
            lastName = newLastName;
        }
        else {
            throw Exception(ErrorCode::invalid_argument);
        }
    }
    void setBirthDate(const String& newBDay) {
        if (isValidDate(bday)) {
            bday = newBDay;
        }
        else {
            throw Exception(ErrorCode::invalid_argument);
        }
    }

    virtual void printInfo() const {
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
    }
};
