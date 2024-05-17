#ifndef DHSETUP_H
#define DHSETUP_H

#include <iostream>
#include <stdexcept>
#include "GaloisField.h"

template <class T>
class DHSetup{
private:
    T generator;

    bool isGenerator(const T& a, const std::vector<unsigned long>& primeFactors) const {
        for (unsigned long q : primeFactors) {
            if (power(a, (T::getCharacteristic() - 1) / q) == T(1))
                return false;
        }
        return true;
    }

public:
    DHSetup() {
        std::random_device rd;
        std::mt19937 gen(rd());
        
        unsigned long characteristic = T::getCharacteristic();
        
        unsigned long pMinusOne = characteristic - 1;
        std::vector<unsigned long> primeFactors;
        for (unsigned long i = 2; i * i <= pMinusOne; ++i) {
            if (pMinusOne % i == 0) {
                primeFactors.push_back(i);
                while (pMinusOne % i == 0)
                    pMinusOne /= i;
            }
        }
        if (pMinusOne > 1)
            primeFactors.push_back(pMinusOne);
        
        unsigned long generatorVal;
        do {
            generatorVal = std::uniform_int_distribution<unsigned long>(2, characteristic - 1)(gen);
            generator = T(generatorVal);
        } while (!isGenerator(generator, primeFactors));
        
        //std::cout << generator << std::endl;
    }

    T getGenerator() const {
        return generator;
    }

    T power(T a, unsigned b) const {
        T result = T(1);
        while (b > 0) {
            if (b % 2 == 0) {
                result *= a;
            }
            a *= a;
            b /= 2;
        }
        return result;
    }
};

#endif