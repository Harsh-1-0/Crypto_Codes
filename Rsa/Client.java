import java.io.*;
import java.math.BigInteger;
import java.net.*;
import java.util.Scanner;

public class Client {
    private static final String SERVER_ADDRESS = "localhost";
    private static final int PORT = 5000;
    private static final BigInteger PUBLIC_KEY = new BigInteger("13");
    private static final BigInteger N = new BigInteger("77");

    public static void main(String[] args) {
        try (Socket socket = new Socket(SERVER_ADDRESS, PORT);
                PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);
                Scanner scanner = new Scanner(System.in)) {

            System.out.print("Enter a number to encrypt and send: ");
            BigInteger M = scanner.nextBigInteger();

            // Encrypting message
            BigInteger C = M.modPow(PUBLIC_KEY, N);
            System.out.println("Encrypted Cipher Text: " + C);

            // Sending encrypted message
            writer.println(C);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
