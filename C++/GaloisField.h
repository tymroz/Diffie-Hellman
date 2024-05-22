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

/*    GaloisField operator*(const GaloisField& other) const {
        return GaloisField(mod(value * other.value, characteristic));
    }
*/

    unsigned long multiplication(unsigned long a, unsigned long b) {
        if (a == 0 || b == 0) {
            return 0;
        }

        if (a == 1) {
            return b;
        }

        if (b == 1){
            return a;
        } 

        unsigned long res = multiplication(a, b / 2);

        if ((b % 2) == 0) {
            return (res + res) % characteristic;
        } 
        
        return ((a % characteristic) + (res + res)) % characteristic;
    }

    GaloisField operator*(const GaloisField& obj) {
        unsigned long res = multiplication(this->value, obj.value);
        
        return GaloisField(res);
    }

/*    GaloisField operator/(const GaloisField& other) const {
        if (other.value == 0) {
            throw std::invalid_argument("Division by zero");
        }
        unsigned long inverse = extendedEuclidean(other.value, characteristic);
        return GaloisField(mod(value * inverse, characteristic));
    }
*/

    unsigned long gcdExtended(unsigned long a, unsigned long b, unsigned long* x, unsigned long* y) {
        if (a == 0) 
        {
            *x = 0, *y = 1;
            return b;
        }
    
        unsigned long x1 = 1, y1 = 1;
        unsigned long gcd = gcdExtended(b % a, a, &x1, &y1);

        *x = y1 - (b / a) * x1;
        *y = x1;
    
        return gcd;
    }

    GaloisField findInverse(unsigned long val) {
        try {
            unsigned long x, y;
            unsigned long g = gcdExtended(val, characteristic, &x, &y);    
            if (g != 1) {
                throw std::runtime_error("Exception caused by findInverse");
            } else {
                return GaloisField(x);
            }
        } catch(const std::exception& e)     {
            std::cerr << e.what() << '\n';
        }

        return GaloisField();     
    }

    GaloisField operator/(const GaloisField& obj) {
        GaloisField res = findInverse(obj.value);
        return (*this) * res;
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
