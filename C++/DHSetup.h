#ifndef DHSETUP_H
#define DHSETUP_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include "GaloisField.h"

template <class T>
class DHSetup{
private:
    T generator;
    
    bool isGenerator(T a, std::vector<unsigned long> primeFactors) {
        unsigned long p = T::getCharacteristic();
        for (unsigned long q : primeFactors) {
            if (power(a, (p - 1) / q) == T(1))
                return false;
        }
        return true;
    }

    bool isPrime(unsigned long n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    std::vector<unsigned long> findprimes(unsigned long n) {
        std::vector<unsigned long> divisors;
        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0 && isPrime(i)) {
                divisors.push_back(i);
                if (i != n / i) {
                    divisors.push_back(n / i);
                }
            }
        }
        return divisors;
    }


public:
    DHSetup() {
        T num;
        unsigned long p = num.getCharacteristic();
        //std::cout << p << std::endl;
        
        std::vector<unsigned long> primes = findprimes(p - 1); 

        std::random_device rd;
        std::mt19937 gen(rd());
        unsigned long generatorVal;
        while(true){
            generatorVal = std::uniform_int_distribution<unsigned long>(1, p - 1)(gen);
            num = T(generatorVal);
            if(isGenerator(num, primes)){
                break;
            }
        }
        generator = num;
        std::cout << "Generator: " << generator << std::endl;
    }

    T getGenerator(){
        return this->generator;
    }

    T power(T a, unsigned long b){
        T result(1);
        while(b > 0){
            if(b % 2 == 1){
                result = (result * a);
            }
            a = (a * a);
            b = b / 2; 
        }
        return result;
    }
};

#endif