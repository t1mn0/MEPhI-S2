#include "String.hpp"

bool isNumber(const String& s) {
    for (int i = 0; i < s.size(); ++i) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

bool isValidDate(const String& s) {
    // valid: DD-MM-YYYY
    if (s.size() != 10)
        return false;

    if (s[2] != '-' || s[5] != '-')
        return false;

    String* day = new String(s.substr(0, 2));
    String* month = new String(s.substr(3, 2));
    String* year = new String(s.substr(6, 4));

    if (!isNumber(*day) || !isNumber(*month) || !isNumber(*year)) {
        return false;
    }

    int dayNum = std::stoi(day->c_str());
    int monthNum = std::stoi(month->c_str());
    int yearNum = std::stoi(year->c_str());

    if (yearNum < 1900)
        return false;

    if (monthNum < 1 || monthNum > 12)
        return false;

    if (dayNum < 1)
        return false;

    if ((monthNum == 1 || monthNum == 3 || monthNum == 5 || monthNum == 7 ||
        monthNum == 8 || monthNum == 10 || monthNum == 12) && dayNum > 31)
        return false;

    if ((monthNum == 4 || monthNum == 6 || monthNum == 9 || monthNum == 11) && dayNum > 30)
        return false;

    if (monthNum == 2) {
        bool isLeapYear = (yearNum % 4 == 0 && (yearNum % 100 != 0 || yearNum % 400 == 0));
        if ((isLeapYear && dayNum > 29) || (!isLeapYear && dayNum > 28))
            return false;
    }

    return true;
}

bool isValidName(const String& name) {
    if (name.size() == 0) {
        return false;
    }

    for (int i = 0; i < name.size(); ++i) {
        if (!isalpha(name[i])) {
            return false;
        }
    }

    return true;
}