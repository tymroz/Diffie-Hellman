import random
import math
from typing import TypeVar, Generic

T = TypeVar('T')
class DHSetup(Generic[T]):
    def __init__(self, num: T):
        self.num = num
        self.primes = None
        self.generator = None

        seed = random.randint(0, 2**32 - 1)
        p = self.num.characteristic

        self.primes = self.sieve_of_eratosthenes(p-1)

        exponent = 0
        ctr = 0
        a = 0
        while True:
            a = random.randint(0, p - 1)

            self.num.setValue(a) 

            ctr = 0
            for i in self.primes:
                exponent = (p - 1) // i

                if self.power(self.num, exponent) != 1:
                    ctr += 1

            if ctr == len(self.primes):
                break

        self.generator = self.num 

    def sieve_of_eratosthenes(self, limit):
        primes = [True] * (limit + 1)
        primes[0] = primes[1] = False
    
        for i in range(2, int(limit ** 0.5) + 1):
            if primes[i]:
                for j in range(i * i, limit + 1, i):
                    primes[j] = False
                
        return [i for i in range(2, limit + 1) if primes[i]]

    def power(self, a: T, b) -> T:
        result = a / a
 
        while b > 0:
            if b % 2 == 1:
                result = (result * a) 
            a *= a  
            b //= 2
        return result