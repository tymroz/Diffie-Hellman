public class Test {
    public static void main(String[] args) {
        GaloisField gf = new GaloisField();
        
        DHSetup<GaloisField> dhSetup = new DHSetup<>(gf);
        
        User<GaloisField> user1 = new User<>(dhSetup);
        User<GaloisField> user2 = new User<>(dhSetup);
        
        GaloisField publicKey1 = user1.getPublicKey();
        GaloisField publicKey2 = user2.getPublicKey();
        
        user1.setKey(publicKey2);
        user2.setKey(publicKey1);
        
        GaloisField encryptionKey1 = user1.getEncryptionKey();
        GaloisField encryptionKey2 = user2.getEncryptionKey();
        

        GaloisField message1 = new GaloisField(42);
        GaloisField message2 = new GaloisField(4452);
        System.out.println("message1: " + message1);
        System.out.println("message2: " + message2);
        GaloisField encryptedMessage1 = user1.encrypt(message1);
        GaloisField encryptedMessage2 = user2.encrypt(message2);
        System.out.println("encryptedMessage1: " + encryptedMessage1);
        System.out.println("encryptedMessage2: " + encryptedMessage2);
        GaloisField decryptedMessage1 = user2.decrypt(encryptedMessage1);
        GaloisField decryptedMessage2 = user1.decrypt(encryptedMessage2);
        System.out.println("decryptedMessage1: " + decryptedMessage1);
        System.out.println("decryptedMessage2: " + decryptedMessage2);

    }
}
