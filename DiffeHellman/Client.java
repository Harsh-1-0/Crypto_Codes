import java.io.*;
import java.math.BigInteger;
import java.net.*;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String SERVER_ADDRESS = "localhost";
        int PORT = 5000;

        // Given values
        int g = 7, p = 23;

        // Taking private key as input
        System.out.print("Enter private key (x): ");
        int x = scanner.nextInt();

        // Compute public key R1 = g^x mod p
        BigInteger R1 = BigInteger.valueOf(g).modPow(BigInteger.valueOf(x), BigInteger.valueOf(p));
        System.out.println("Computed Public Key (R1): " + R1);

        try (Socket socket = new Socket(SERVER_ADDRESS, PORT);
                PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);
                BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {

            // Send R1 to Server
            writer.println(R1);

            // Receive R2 from Server
            String R2_str = reader.readLine();
            BigInteger R2 = new BigInteger(R2_str);
            System.out.println("Received Public Key (R2) from Server: " + R2);

            // Compute symmetric key K = R2^x mod p
            BigInteger K = R2.modPow(BigInteger.valueOf(x), BigInteger.valueOf(p));
            System.out.println("Computed Symmetric Key (K): " + K);

        } catch (IOException e) {
            e.printStackTrace();
        }

        scanner.close();
    }
}
