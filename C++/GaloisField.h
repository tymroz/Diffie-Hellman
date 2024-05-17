#ifndef GALOISFIELD_H
#define GALOISFIELD_H

#include <iostream>
#include <stdexcept>

class GaloisField {
private:
    static const unsigned characteristic = 1234567891;

    unsigned value;

    int mod(int a, int b) const {
        return (a % b + b) % b;
    }

    int extendedEuclidean(int a, int b) const {
        int old_r = a, r = b;
        int old_s = 1, s = 0;
        int old_t = 0, t = 1;

        while (r != 0) {
            int quotient = old_r / r;

            int temp = r;
            r = old_r - quotient * r;
            old_r = temp;

            temp = s;
            s = old_s - quotient * s;
            old_s = temp;

            temp = t;
            t = old_t - quotient * t;
            old_t = temp;
        }

        return mod(old_s, characteristic);
    }

public:
    GaloisField() : value(0) {}

    GaloisField(int val) : value(mod(val, characteristic)) {}

    int getValue() const {
        return value;
    }

    static int getCharacteristic() {
        return characteristic;
    }

    GaloisField operator+(const GaloisField& other) const {
        return GaloisField(mod(value + other.value, characteristic));
    }

    GaloisField operator-(const GaloisField& other) const {
        return GaloisField(mod(value - other.value, characteristic));
    }

    GaloisField operator*(const GaloisField& other) const {
        return GaloisField(mod(value * other.value, characteristic));
    }

    GaloisField operator/(const GaloisField& other) const {
        if (other.value == 0) {
            throw std::invalid_argument("Division by zero");
        }
        int inverse = extendedEuclidean(other.value, characteristic);
        return GaloisField(mod(value * inverse, characteristic));
    }

    bool operator==(const GaloisField& other) const {
        return value == other.value;
    }

    bool operator!=(const GaloisField& other) const {
        return !(*this == other);
    }

    bool operator<(const GaloisField& other) const {
        return value < other.value;
    }

    bool operator<=(const GaloisField& other) const {
        return value <= other.value;
    }

    bool operator>(const GaloisField& other) const {
        return value > other.value;
    }

    bool operator>=(const GaloisField& other) const {
        return value >= other.value;
    }

    GaloisField& operator+=(const GaloisField& other) {
        *this = *this + other;
        return *this;
    }

    GaloisField& operator-=(const GaloisField& other) {
        *this = *this - other;
        return *this;
    }

    GaloisField& operator*=(const GaloisField& other) {
        *this = *this * other;
        return *this;
    }

    GaloisField& operator/=(const GaloisField& other) {
        *this = *this / other;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const GaloisField& finiteField) {
        os << finiteField.value;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, GaloisField& finiteField) {
        int val;
        is >> val;
        finiteField = GaloisField(val);
        return is;
    }
};

#endif // GALOISFIELD_H
