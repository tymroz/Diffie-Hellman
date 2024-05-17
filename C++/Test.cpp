#include <iostream>
#include <random>
#include "GaloisField.h"
#include "DHSetup.h"
#include "User.h"

int main() {
    DHSetup<GaloisField> setup;

    User<GaloisField> user1(setup);
    User<GaloisField> user2(setup);

    GaloisField message1;
    GaloisField message2;

    std::cout << "user1 message: ";
    std::cin >> message1;
    std::cout << "user2 message: ";
    std::cin >> message2;

    user1.setKey(user2.getPublicKey());
    user2.setKey(user1.getPublicKey());

    std::cout << user1.publicKey << " " << user1.encryptionKey << std::endl;
    std::cout << user2.publicKey << " " << user2.encryptionKey << std::endl;

    GaloisField encrypted1 = user1.encrypt(message1);
    GaloisField encrypted2 = user2.encrypt(message2);
    std::cout << "encrypted: " << encrypted1 << "\n";
    std::cout << "encrypted: " << encrypted2 << "\n";

    GaloisField decrypted1 = user2.decrypt(encrypted1);
    GaloisField decrypted2 = user1.decrypt(encrypted2);
    std::cout << "decrypted: " << decrypted1 << "\n";
    std::cout << "decrypted: " << decrypted2 << "\n";

    return 0;
}
