import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.function.Supplier;

public class DHSetup<T extends Field> {
    private final T generator;
    Supplier<T> cons;
    public DHSetup(Supplier<T> cons) {
        this.cons = cons;

        T num = cons.get();
        int p = num.getCharacteristic();
        List<Integer> primes = findPrimes(p - 1);

        long exponent;
        int ctr;
        Random random = new Random();
        do {
            num.setValue(random.nextInt(p - 1));

            ctr = 0;
            for (int i : primes) {
                exponent = (p - 1) / i;

                if (power(num, exponent).ifNotEqual(1)) {
                    ctr++;
                }
            }

        } while (ctr != primes.size());

        generator = num;
    }

    private List<Integer> findPrimes(int num) {
        List<Integer> primes = new ArrayList<>();

        if(num % 2 == 0) {
            primes.add(2);
        }

        for(int i = 3; i < Math.sqrt(num); i += 2) {

            if (num % i == 0) {
                primes.add(i);
            }
        }
        return primes;
    }

    public T power(T a, long b) {
        T res = cons.get();
        res.setValue(1);
        while(b > 0) {
            if(b % 2 == 1) {
                res.assign(res.mult(a));
            }
            a.assign(a.mult(a));
            b = b / 2;
        }
        return res;
    }

    public T getGenerator() {
        return generator;
    }
}