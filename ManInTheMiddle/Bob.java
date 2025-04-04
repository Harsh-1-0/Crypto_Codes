import java.io.*;
import java.math.BigInteger;
import java.net.*;
import java.util.Scanner;

public class Bob {
    private static final String SERVER_ADDRESS = "localhost";
    private static final int PORT = 5000;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter prime number (p): ");
        int p = scanner.nextInt();
        System.out.print("Enter generator (g): ");
        int g = scanner.nextInt();
        System.out.print("Enter Bob's private key (y): ");
        int y = scanner.nextInt();

        try (Socket socket = new Socket(SERVER_ADDRESS, PORT);
                PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);
                BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {

            BigInteger R2 = BigInteger.valueOf(g).modPow(BigInteger.valueOf(y), BigInteger.valueOf(p));
            System.out.println("Bob's Public Key (R2): " + R2);

            writer.println(R2);

            String fakePublicKeyStr = reader.readLine();
            BigInteger fakePublicKey = new BigInteger(fakePublicKeyStr);
            System.out.println("Bob received (Fake) Public Key: " + fakePublicKey);

            BigInteger sharedKey = fakePublicKey.modPow(BigInteger.valueOf(y), BigInteger.valueOf(p));
            System.out.println("Bob's Computed Shared Key: " + sharedKey);

        } catch (IOException e) {
            e.printStackTrace();
        }

        scanner.close();
    }
}
