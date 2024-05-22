#include <iostream>
#include <random>
#include "GaloisField.h"
#include "DHSetup.h"
#include "User.h"

int main() {
    DHSetup<GaloisField> setup;

    User<GaloisField> alice(setup);
    GaloisField publicKey1 = alice.getPublicKey();

    User<GaloisField> bob(setup);
    GaloisField publicKey2 = bob.getPublicKey();

    alice.setKey(publicKey2);
    bob.setKey(publicKey1);

    GaloisField key1 = alice.getEncryptionKey();
    GaloisField key2 = bob.getEncryptionKey();

/*    if (key1 == key2) {
        std::cout << "Keys match: " << key1 << std::endl;
    } else {
        std::cerr << "Keys do not match. Key1: " << key1 << ", Key2: " << key2 << std::endl;
    }
*/
    //std::cout << setup.power(GaloisField(123456789), 89);

    GaloisField message1 = GaloisField(2345);
    GaloisField message2 = GaloisField(167);  
    std::cout << "message1: " << message1 << "\n";
    std::cout << "message2: " << message2 << "\n";

    GaloisField encrypted1 = alice.encrypt(message1);
    GaloisField encrypted2 = bob.encrypt(message2);
    std::cout << "encrypted1: " << encrypted1 << "\n";
    std::cout << "encrypted2: " << encrypted2 << "\n";

    GaloisField decrypted1 = bob.decrypt(encrypted1);
    GaloisField decrypted2 = alice.decrypt(encrypted2);
    std::cout << "decrypted1: " << decrypted1 << "\n";
    std::cout << "decrypted2: " << decrypted2 << "\n";

    return 0;
}
