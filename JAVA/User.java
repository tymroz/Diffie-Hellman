import java.util.Random;

public class User<T extends GaloisField> {
    private DHSetup<T> setup;
    private long secret;
    private boolean keySet;
    private T encryptionKey;

    public User(DHSetup<T> setupRef) {
        this.setup = setupRef;
        this.keySet = false;
        Random rand = new Random();
        this.secret = 1 + rand.nextInt(100);
    }

    public T getPublicKey() {
        return setup.power(setup.getGenerator(), secret);
    }

    public void setKey(T a) {
        if (!keySet) {
            encryptionKey = setup.power(a, secret);
            keySet = true;
        } else {
            System.err.println("Encryption key already set.");
        }
    }

    public T getEncryptionKey() {
        if (!keySet) {
            System.err.println("Encryption key not set.");
            return null;
        }
        return encryptionKey;
    }

    public T encrypt(T m) {
        if (!keySet) {
            System.err.println("Encryption key not set.");
            return null;
        }
        return (T) m.multiply(encryptionKey);
    }

    public T decrypt(T c) {
        if (!keySet) {
            System.err.println("Encryption key not set.");
            return null;
        }
        return (T) c.divide(encryptionKey);
    }

    public static void main(String[] args) {
        GaloisField gf = new GaloisField();
        DHSetup<GaloisField> dhSetup = new DHSetup<>(gf);
        User<GaloisField> user = new User<>(dhSetup);

        GaloisField publicKey = user.getPublicKey();
        System.out.println("Public Key: " + publicKey);

        user.setKey(publicKey);
        GaloisField encryptionKey = user.getEncryptionKey();
        System.out.println("Encryption Key: " + encryptionKey);

        GaloisField message = new GaloisField(42);
        GaloisField encryptedMessage = user.encrypt(message);
        System.out.println("Encrypted Message: " + encryptedMessage);

        GaloisField decryptedMessage = user.decrypt(encryptedMessage);
        System.out.println("Decrypted Message: " + decryptedMessage);
    }
}
