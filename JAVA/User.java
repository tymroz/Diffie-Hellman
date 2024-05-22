import java.util.Random;

public class User<T extends Field>{
    private DHSetup<T> setup;
    private int secret;
    public T key;
    public User(DHSetup<T> setup) {
        this.setup = setup;

        Random rand = new Random();
        secret = rand.nextInt(50) + 1;
    }

    public T getPublicKey() {
        return setup.power(setup.getGenerator(), secret);
    }

    public void setKey(T a) {
        this.key = setup.power(a, secret);
    }

    public T encrypt(T m) {
        try {
            if(key.getValue() != 0) {
                T res = setup.cons.get();
                res.assign(m.mult(key));
                return res;
            } else {
                throw new Exception();
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        return null;
    }

    public T decrypt(T c) {
        try {
            if(key.getValue() != 0) {
                T res = setup.cons.get();
                res.assign(c.div(key));
                return res;
           } else {
                throw new Exception();
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        return null;
    }
}