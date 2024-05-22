#ifndef USER_H
#define USER_H

#include <iostream>
#include <stdexcept>
#include "GaloisField.h"
#include "DHSetup.h"

template <class T>
class User{
private:
    DHSetup<T> setup;
    T secret;
    bool keySet;
    T publicKey;
    T encryptionKey;
public:
    User(DHSetup<T>& setupRef) : setup(setupRef), keySet(false) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<unsigned long> dis(2, 100);
        unsigned long secretVal = dis(gen);
        secret = T(secretVal);
        std::cout << "Secret: " << secret << std::endl;
        //std::cout << "Generator: " << setup.getGenerator() << std::endl;
        publicKey = setup.power(setup.getGenerator(), secret.getValue());
        std::cout << "Public: " << publicKey << std::endl;
        //std::cout << setup.power(T(3396308011), 20) << std::endl;
    }

    T getPublicKey() const {
        return publicKey;
    }

    void setKey(T a) {
        if (!keySet) {
            encryptionKey = setup.power(a, secret.getValue());
            std::cout << "Encryption: " << encryptionKey << std::endl;
            keySet = true;
        } else {
            std::cerr << "Encryption key already set.\n";
        }
    }

    T getEncryptionKey() const {
        if (!keySet) {
            std::cerr << "Encryption key not set.\n";
            return T();
        }
        return encryptionKey;
    }

    T encrypt(T m) const {
        if (!keySet) {
            std::cerr << "Encryption key not set.\n";
            return T();
        }
        return m *= encryptionKey;
    }

    T decrypt(T c) const {
        if (!keySet) {
            std::cerr << "Encryption key not set.\n";
            return T();
        }
        return c /= encryptionKey;
    }
};

#endif