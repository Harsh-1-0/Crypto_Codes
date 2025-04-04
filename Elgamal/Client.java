
import java.io.*;
import java.math.BigInteger;
import java.net.*;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String SERVER_ADDRESS = "localhost";
        int PORT = 5000;

        // First case: P=19, g=10, privateKey=5, M=13, randomInteger=6
        System.out.println("Enter Prime number");
        int P = sc.nextInt();
        System.out.println("Enter primitive root of " + P);
        int g = sc.nextInt();
        System.out.println("Enter private key");
        int privateKey = sc.nextInt();
        System.out.println("Enter message to be encrypted");
        int M = sc.nextInt();
        System.out.println("Enter random integer");
        int randomInteger = sc.nextInt();
        sc.close();
        // Public key generation
        BigInteger e1 = BigInteger.valueOf(g);
        BigInteger e2 = e1.modPow(BigInteger.valueOf(privateKey), BigInteger.valueOf(P));

        // Encryption
        BigInteger C1 = e1.modPow(BigInteger.valueOf(randomInteger), BigInteger.valueOf(P));
        BigInteger C2 = (BigInteger.valueOf(M)
                .multiply(e2.modPow(BigInteger.valueOf(randomInteger), BigInteger.valueOf(P))))
                .mod(BigInteger.valueOf(P));

        System.out.println("Encrypted values: C1 = " + C1 + ", C2 = " + C2);

        try (Socket socket = new Socket(SERVER_ADDRESS, PORT);
                PrintWriter writer = new PrintWriter(socket.getOutputStream(), true)) {

            writer.println(P + "," + privateKey + "," + C1 + "," + C2);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
