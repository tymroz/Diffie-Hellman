from FiniteField import FiniteField
from DHSetup import DHSetup
from User import User
import sys

def main():
    field = FiniteField()
    setup = DHSetup(field)

    user1 = User(setup)
    user2 = User(setup)

    message1 = FiniteField()
    message2 = FiniteField()

    print("user1 message: 432")
    message1_input = int(432) 
    message1.setValue(message1_input)

    print("user2 message: 92864")
    message2_input = int(92864)  
    message2.setValue(message2_input)

    public1 = user2.get_public_key()
    public2 = user1.get_public_key()
    user1.set_key(public1)
    user2.set_key(public2)

    encrypted1 = user1.encrypt(message1)
    encrypted2 = user2.encrypt(message2)
    print("encrypted:", encrypted1)
    print("encrypted:", encrypted2)

    decrypted1 = user2.decrypt(encrypted1)
    decrypted2 = user1.decrypt(encrypted2)
    print("decrypted:", decrypted1)
    print("decrypted:", decrypted2)

if __name__ == "__main__":
    main()