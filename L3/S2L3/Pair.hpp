#pragma once

template <typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;

    Pair() : first(T1()), second(T2()) {}

    Pair(const T1& first, const T2& second) : first(first), second(second) {}

    Pair(const Pair<T1, T2>& other) : first(other.first), second(other.second) {}

    Pair& operator=(const Pair<T1, T2>& other) {
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }

    ~Pair() {}
};

