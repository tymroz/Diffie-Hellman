import random
from typing import TypeVar, Generic

T = TypeVar('T')
class User(Generic[T]):
    def __init__(self, setup):
        self.setup = setup

        seed = random.randint(0, 2**32 - 1)
        distribution = random.randint(1, 50)  
        self.secret = distribution 

    def get_public_key(self) -> T:
        generator = self.setup.generator
        return self.setup.power(generator, self.secret)

    def set_key(self, a: T):
        self.key = self.setup.power(a, self.secret)

    def decrypt(self, c: T) -> T:
        try:
            if self.key != 0:
                return c / self.key
            else:
                raise RuntimeError("Key has not been set up!")
        except RuntimeError as e:
            print(e)
    
    def encrypt(self, m: T) -> T:
        try:
            if self.key != 0:
                return m * self.key
            else:
                raise RuntimeError("Key has not been set up!")
        except RuntimeError as e:
            print(e)