class GaloisField {
    private static final long characteristic = 1234577;
    private long value;

    private long mod(long a, long b) {
        return (a % b + b) % b;
    }

    private long extendedEuclidean(long a, long b) {
        long old_r = a, r = b;
        long old_s = 1, s = 0;
        long old_t = 0, t = 1;

        while (r != 0) {
            long quotient = old_r / r;

            long temp = r;
            r = old_r - quotient * r;
            old_r = temp;

            temp = s;
            s = old_s - quotient * s;
            old_s = temp;

            temp = t;
            t = old_t - quotient * t;
            old_t = temp;
        }

        return mod(old_s, characteristic);
    }

    public GaloisField() {
        this.value = 0;
    }

    public GaloisField(long val) {
        this.value = mod(val, characteristic);
    }

    public long getValue() {
        return value;
    }

    public GaloisField add(GaloisField other) {
        return new GaloisField(mod(value + other.value, characteristic));
    }

    public GaloisField subtract(GaloisField other) {
        return new GaloisField(mod(value - other.value, characteristic));
    }

    private long multiplication(long a, long b) {
        if (a == 0 || b == 0) {
            return 0;
        }

        if (a == 1) {
            return b;
        }

        if (b == 1) {
            return a;
        }

        long res = multiplication(a, b / 2);

        if ((b % 2) == 0) {
            return (res + res) % characteristic;
        }

        return ((a % characteristic) + (res + res)) % characteristic;
    }

    public GaloisField multiply(GaloisField other) {
        long res = multiplication(this.value, other.value);
        return new GaloisField(res);
    }

    private long gcdExtended(long a, long b, long[] xy) {
        if (a == 0) {
            xy[0] = 0;
            xy[1] = 1;
            return b;
        }

        long[] xy1 = {1, 1};
        long gcd = gcdExtended(b % a, a, xy1);

        xy[0] = xy1[1] - (b / a) * xy1[0];
        xy[1] = xy1[0];

        return gcd;
    }

    public GaloisField findInverse(long val) {
        long[] xy = {1, 1};
        long g = gcdExtended(val, characteristic, xy);
        if (g != 1) {
            throw new RuntimeException("Exception caused by findInverse");
        } else {
            return new GaloisField(xy[0]);
        }
    }

    public GaloisField divide(GaloisField other) {
        if (other.value == 0) {
            throw new IllegalArgumentException("Division by zero");
        }
        GaloisField res = findInverse(other.value);
        return this.multiply(res);
    }

    public boolean equals(GaloisField other) {
        return value == other.value;
    }

    public boolean notEquals(GaloisField other) {
        return !equals(other);
    }

    public boolean lessThan(GaloisField other) {
        return value < other.value;
    }

    public boolean lessThanOrEqual(GaloisField other) {
        return value <= other.value;
    }

    public boolean greaterThan(GaloisField other) {
        return value > other.value;
    }

    public boolean greaterThanOrEqual(GaloisField other) {
        return value >= other.value;
    }

    public GaloisField addAssign(GaloisField other) {
        this.value = mod(this.value + other.value, characteristic);
        return this;
    }

    public GaloisField subtractAssign(GaloisField other) {
        this.value = mod(this.value - other.value, characteristic);
        return this;
    }

    public GaloisField multiplyAssign(GaloisField other) {
        this.value = mod(this.value * other.value, characteristic);
        return this;
    }

    public GaloisField divideAssign(GaloisField other) {
        if (other.value == 0) {
            throw new IllegalArgumentException("Division by zero");
        }
        long inverse = extendedEuclidean(other.value, characteristic);
        this.value = mod(this.value * inverse, characteristic);
        return this;
    }

    @Override
    public String toString() {
        return String.valueOf(value);
    }

    public GaloisField createInstance(long value) {
        return new GaloisField(value);
    }

    public GaloisField getOne() {
        return new GaloisField(1);
    }

    public static long getCharacteristic() {
        return characteristic;
    }
}
