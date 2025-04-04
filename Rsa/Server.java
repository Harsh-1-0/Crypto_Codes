import java.io.*;
import java.math.BigInteger;
import java.net.*;

public class Server {
    private static final int PORT = 5000;
    private static final BigInteger PRIVATE_KEY = new BigInteger("37");
    private static final BigInteger N = new BigInteger("77");

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Alice's Server is running...");

            while (true) {
                Socket socket = serverSocket.accept();
                System.out.println("Connected to Bob...");

                BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String encryptedText = reader.readLine();

                if (encryptedText != null) {
                    BigInteger C = new BigInteger(encryptedText);
                    System.out.println("Received Cipher Text: " + C);

                    // Decrypting message
                    BigInteger M = C.modPow(PRIVATE_KEY, N);
                    System.out.println("Decrypted Message (Plaintext): " + M);
                }

                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
