#ifndef GALOISFIELD_H
#define GALOISFIELD_H

#include <iostream>
#include <stdexcept>

class GaloisField {
private:
    static const unsigned long characteristic = 1234567891;

    unsigned long value;

    unsigned long mod(unsigned long a, unsigned long b) const {
        return (a % b + b) % b;
    }

    unsigned long extendedEuclidean(unsigned long a, unsigned long b) const {
        unsigned long old_r = a, r = b;
        unsigned long old_s = 1, s = 0;
        unsigned long old_t = 0, t = 1;

        while (r != 0) {
            unsigned long quotient = old_r / r;

            unsigned long temp = r;
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

    GaloisField(unsigned long val) : value(mod(val, characteristic)) {}

    unsigned long getValue() const {
        return value;
    }

    static unsigned long getCharacteristic() {
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
        unsigned long inverse = extendedEuclidean(other.value, characteristic);
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
        unsigned long val;
        is >> val;
        finiteField = GaloisField(val);
        return is;
    }
};

#endif // GALOISFIELD_H
