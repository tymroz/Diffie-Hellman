import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class DHSetup<T extends GaloisField> {
    private T generator;

    private boolean isGenerator(T a, List<Long> primeFactors) {
        long p = T.getCharacteristic();
        for (long q : primeFactors) {
            if (power(a, (p - 1) / q).equals(a.getOne())) {
                return false;
            }
        }
        return true;
    }

    private boolean isPrime(long n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    private List<Long> findPrimes(long n) {
        List<Long> divisors = new ArrayList<>();
        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                if (isPrime(i)) {
                    divisors.add((long) i);
                }
                if (i != n / i && isPrime(n / i)) {
                    divisors.add(n / i);
                }
            }
        }
        return divisors;
    }

    public DHSetup(T num) {
        long p = num.getCharacteristic();
        List<Long> primes = findPrimes(p - 1);

        Random rand = new Random();
        T generatorVal;
        while (true) {
            int randomVal = 1 + rand.nextInt((int) (p - 1));
            generatorVal = (T) num.createInstance(randomVal);
            if (isGenerator(generatorVal, primes)) {
                break;
            }
        }
        generator = generatorVal;
    }

    public T getGenerator() {
        return this.generator;
    }

    public T power(T a, long b) {
        T result = (T) a.getOne();
        while (b > 0) {
            if (b % 2 == 1) {
                result = (T) result.multiply(a);
            }
            a = (T) a.multiply(a);
            b = b / 2;
        }
        return result;
    }
}
