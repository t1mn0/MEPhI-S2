#pragma once
#include <iostream>
#include "../../../../L2/S2L2/MutableArraySequence.hpp"

class String {
private:
    MutableArraySequence<char> arrayseq;
public:
    String() {}

    String(const char* cstr) {
        while (*cstr != '\0') {
            arrayseq.push_back(*cstr++);
        }
    }

    String(const String& other){
        this->arrayseq.clear();
        for (int i = 0; i < other.size(); ++i) {
            arrayseq.push_back(other.arrayseq.get(i));
        }
    }

    ~String() {}

    String& operator=(const String& other) {
        if (this != &other) {
            arrayseq.clear();
            for (int i = 0; i < other.size(); ++i) {
                arrayseq.push_back(other[i]);
            }
        }
        return *this;
    }

    char operator[](int index) const {
        return arrayseq.get(index);
    }

    bool operator==(const String& other) const {
        if (other.size() != this->size()) return false;
        for (int i = 0; i < other.size(); ++i) {
            if (this->operator[](i) != other.operator[](i)) {
                return false;
            }
        }
        return true;
    }

    void push_back(char c) {
        arrayseq.push_back(c);
    }

    void push_back(const String& str) {
        for (int i = 0; i < str.size(); ++i) {
            arrayseq.push_back(str[i]);
        }
    }

    void push_front(char c) {
        arrayseq.push_front(c);
    }

    void push_front(const String& str) {
        for (int i = 0; i < str.size(); ++i) {
            arrayseq.push_front(str[i]);
        }
    }

    void clear() {
        arrayseq.clear();
    }

    size_t size() const {
        return arrayseq.get_size();
    }

    bool empty() const {
        return arrayseq.empty();
    }

    String substr(int start, int length) const {
        if (start < 0 || length < 0 || start + length > arrayseq.get_size()) {
            return String();
        }

        String result;
        for (int i = start; i < start + length; ++i) {
            result.push_back(arrayseq.get(i));
        }

        return result;
    }

    const char* c_str() {
        char* buffer = new char[this->size() + 1];
        for (int i = 0; i < this->size(); ++i) {
            buffer[i] = arrayseq.get(i);
        }
        buffer[this->size()] = '\0';
        return buffer;
    }

};
