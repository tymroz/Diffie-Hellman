import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class FiniteField extends Field {
    private int value;
    private static final int characteristic = 1234567891;
    public FiniteField() {
        this.value = 0;
    }

    public FiniteField(int value) {
        setValue(value);
    }

    public void setValue(int value) {
        while(value < 0) {
            value += characteristic;
        }

        this.value = value % characteristic;
    }

    public int getValue() {
        return this.value;
    }

    public int getCharacteristic() {
        return characteristic;
    }

    private FiniteField findInverse(int value) {
        int[] res = new int[2];
        try {
            int g = gcdExtended(value, characteristic, res);
            if (g != 1) {
                throw new Exception();
            }
            else {
                int inverse = (res[0] % characteristic + characteristic) % characteristic;
                return new FiniteField(inverse);
            }
        }
        catch(Exception e)
        {
            System.out.println("Inverse not found");
        }

        return new FiniteField();
    }

    private int gcdExtended(int a, int b, int[] res) {
        if (a == 0) {
            res[0] = 0;
            res[1] = 1;
            return b;
        }

        // To store results of recursive call
        int gcd = gcdExtended(b % a, a, res);
        int x1 = res[0];
        int y1 = res[1];

        // Update x and y using results of recursive
        // call
        int tmp = b / a;
        res[0] = y1 - tmp * x1;
        res[1] = x1;

        return gcd;
    }

    public Field add(final Field obj) {
        return new FiniteField(this.value + obj.getValue());
    }

    public Field sub(final Field obj) {
        int result = this.value - obj.getValue();
        return new FiniteField(result);
    }

    public Field mult(final Field obj) {
        int res = fastMultiplication(this.value, obj.getValue());
        return new FiniteField(res);
    }

    private int fastMultiplication(int a, int b) {
        if (a == 0 || b == 0)
        {
            return 0;
        }

        if (a == 1)
        {
            return b;
        }

        if (b == 1)
        {
            return a;
        }

        int res = fastMultiplication(a, b / 2);

        if ((b % 2) == 0)
        {
            return (res + res) % characteristic;
        }
        else
        {
            return ((a % characteristic) + (res + res)) % characteristic;
        }
    }

    public Field div(final Field obj) {
        FiniteField inv = findInverse(obj.getValue());
        return inv.mult(this);
    }

    public void assign(final Object obj) {
        if (obj instanceof FiniteField other) {
            this.setValue(other.value);
        } else if (obj instanceof Integer) {
           this.setValue((int)obj);
        }
    }

    public void multAndAssign(final Field obj) {
        assign(mult(obj));
    }

    public void divAndAssign(final Field obj) {
        assign(div(obj));
    }

    public void addAndAssign(final Field obj) {
        assign(add(obj));
    }

    public void subAndAssign(final Field obj) {
        assign(sub(obj));
    }

    public boolean ifNotEqual(final Object obj) {
        if (obj instanceof FiniteField other) {
            return this.value != other.value;
        } else if (obj instanceof Integer) {
            return this.value != (int) obj;
        }
        return false;
    }

    public boolean ifEqual(final Object obj) {
        if (obj instanceof FiniteField other) {
            return this.value == other.value;
        } else if (obj instanceof Integer) {
            return this.value == (int) obj;
        }
        return false;
    }

    public boolean ifLessEqual(final Object obj) {
        if (obj instanceof FiniteField other) {
            return this.value <= other.value;
        } else if (obj instanceof Integer) {
            return this.value <= (int) obj;
        }
        return false;
    }

    public boolean ifGreaterEqual(final Object obj) {
            if (obj instanceof FiniteField other) {
                return this.value >= other.value;
            } else if (obj instanceof Integer) {
                return this.value >= (int) obj;
            }
            return false;
    }

    public boolean ifLess(final Object obj) {
        if (obj instanceof FiniteField other) {
            return this.value < other.value;
        } else if (obj instanceof Integer) {
            return this.value < (int) obj;
        }
        return false;
    }

    public boolean ifGreater(final Object obj) {
        if (obj instanceof FiniteField other) {
            return this.value > other.value;
        } else if (obj instanceof Integer) {
            return this.value > (int) obj;
        }
        return false;
    }

    public static void stdinRead(Field a)  {
        try {
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            FiniteField b = new FiniteField(Integer.parseInt(br.readLine()));
            a.assign(b);
        } catch (IOException ex){
            System.out.println("IO exception");
        }
    }
    @Override
    public String toString() {
        return String.valueOf(value);
    }
}