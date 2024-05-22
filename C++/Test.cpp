#include <iostream>
#include <random>
#include "GaloisField.h"
#include "DHSetup.h"
#include "User.h"

int main() {
    DHSetup<GaloisField> setup;

    std::cout << "Alice: \n";
    User<GaloisField> alice(setup);
    GaloisField publicKey1 = alice.getPublicKey();

    std::cout << "Bob: \n";
    User<GaloisField> bob(setup);
    GaloisField publicKey2 = bob.getPublicKey();

    //GaloisField message1 = GaloisField(2345);
    //GaloisField message2 = GaloisField(167);

    std::cout << "Alice: \n";
    alice.setKey(publicKey2);
    std::cout << "Bob: \n";
    bob.setKey(publicKey1);

    GaloisField key1 = alice.getEncryptionKey();
    GaloisField key2 = bob.getEncryptionKey();

    if (key1 == key2) {
        std::cout << "Keys match: " << key1 << std::endl;
    } else {
        std::cerr << "Keys do not match. Key1: " << key1 << ", Key2: " << key2 << std::endl;
    }

/*    GaloisField encrypted1 = alice.encrypt(message1);
    GaloisField encrypted2 = bob.encrypt(message2);
    std::cout << "encrypted: " << encrypted1 << "\n";
    std::cout << "encrypted: " << encrypted2 << "\n";

    GaloisField decrypted1 = bob.decrypt(encrypted1);
    GaloisField decrypted2 = alice.decrypt(encrypted2);
    std::cout << "decrypted: " << decrypted1 << "\n";
    std::cout << "decrypted: " << decrypted2 << "\n";
*/
    return 0;
}
