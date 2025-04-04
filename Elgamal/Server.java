
import java.io.*;
import java.math.BigInteger;
import java.net.*;

public class Server {
    public static void main(String[] args) {
        int PORT = 5000;

        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("ElGamal Decryption Server is running...");

            while (true) {
                Socket socket = serverSocket.accept();
                System.out.println("Client connected...");

                BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String receivedData = reader.readLine();

                if (receivedData != null) {
                    String[] parts = receivedData.split(",");
                    int P = Integer.parseInt(parts[0]);
                    int privateKey = Integer.parseInt(parts[1]);
                    BigInteger C1 = new BigInteger(parts[2]);
                    BigInteger C2 = new BigInteger(parts[3]);

                    System.out.println("Received: C1 = " + C1 + ", C2 = " + C2);

                    // Decryption
                    BigInteger C1_inverse = C1.modPow(BigInteger.valueOf(P - 1 - privateKey), BigInteger.valueOf(P));
                    BigInteger M = (C2.multiply(C1_inverse)).mod(BigInteger.valueOf(P));

                    System.out.println("Decrypted Message: " + M);
                }

                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
