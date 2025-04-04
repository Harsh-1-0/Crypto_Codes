import java.io.*;
import java.math.BigInteger;
import java.net.*;
import java.util.Scanner;

public class Server {
    public static void main(String[] args) {
        int PORT = 5000;

        // Given values
        int g = 7, p = 23;

        Scanner scanner = new Scanner(System.in);

        // Taking private key as input
        System.out.print("Enter private key (y): ");
        int y = scanner.nextInt();

        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Diffie-Hellman Key Exchange Server is running...");

            while (true) {
                Socket socket = serverSocket.accept();
                System.out.println("Client connected...");

                BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);

                // Receive R1 from Client
                String R1_str = reader.readLine();
                BigInteger R1 = new BigInteger(R1_str);
                System.out.println("Received Public Key (R1) from Client: " + R1);

                // Compute public key R2 = g^y mod p
                BigInteger R2 = BigInteger.valueOf(g).modPow(BigInteger.valueOf(y), BigInteger.valueOf(p));
                System.out.println("Computed Public Key (R2): " + R2);

                // Send R2 to Client
                writer.println(R2);

                // Compute symmetric key K = R1^y mod p
                BigInteger K = R1.modPow(BigInteger.valueOf(y), BigInteger.valueOf(p));
                System.out.println("Computed Symmetric Key (K): " + K);

                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        scanner.close();
    }
}
