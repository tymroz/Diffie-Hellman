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
    unsigned long secret;
    bool keySet;
    T encryptionKey;
public:
    User(DHSetup<T>& setupRef) : setup(setupRef), keySet(false) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<unsigned long> dis(1, 100);
        secret = dis(gen);
        //std::cout << "Secret: " << secret << std::endl;
    }

    T getPublicKey(){
        T privateKey = setup.power(setup.getGenerator(), secret);
        //std::cout << privateKey << std::endl;
        return privateKey;
    }

    void setKey(T a) {
        if (!keySet) {
            encryptionKey = setup.power(a, secret);
            //std::cout << "Encryption: " << encryptionKey << std::endl;
            keySet = true;
        } else {
            std::cerr << "Encryption key already set.\n";
        }
    }

    T getEncryptionKey(){
        if (!keySet) {
            std::cerr << "Encryption key not set.\n";
            return T();
        }
        return encryptionKey;
    }

    T encrypt(T m){
        if (!keySet) {
            std::cerr << "Encryption key not set.\n";
            return T();
        }
        T result = m * encryptionKey;
        return result;
    }

    T decrypt(T c){
        if (!keySet) {
            std::cerr << "Encryption key not set.\n";
            return T();
        }
        T result = c / encryptionKey;
        return result;
    }
};

#endif