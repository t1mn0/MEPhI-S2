#pragma once

#include <iostream>
#include "_StringUtilitie_.hpp"

class PersonID {
private:
    static int nextID;
    int id;

public:
    PersonID() {
        id = nextID;
        nextID++;
    }

    int getID() const{
        return id;
    }
};

class Person {
private:
    PersonID id;
    String firstName;
    String middleName;
    String lastName;
    String bday;

public:
    Person() {}

    Person(const String& firstName, const String& middleName, const String& lastName, const String& bday) {
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

    ~Person() {}

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
            this->middleName = newMiddleName;
        }
        else {
            throw Exception(ErrorCode::invalid_argument);
        }
    }
    void setLastName(const String& newLastName) {
        if (isValidName(newLastName)) {
            this->lastName = newLastName;
        }
        else {
            throw Exception(ErrorCode::invalid_argument);
        }
    }
    void setBirthDate(const String& newBDay) {
        if (isValidDate(this->bday)) {
            bday = newBDay;
        }
        else {
            throw Exception(ErrorCode::invalid_argument);
        }
    }

    virtual void printInfo() const {
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
        std::cout << "\n |__________________________________\n";
    }
};