import java.io.*;
import java.math.BigInteger;
import java.net.*;
import java.util.Scanner;

public class Server {
    public static void main(String[] args) {
        int PORT = 5000;

        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("ECC ElGamal Decryption Server is running...");

            while (true) {
                Socket socket = serverSocket.accept();
                System.out.println("Client connected...");

                BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String receivedData = reader.readLine();

                if (receivedData != null) {
                    String[] parts = receivedData.split(",");
                    int p = Integer.parseInt(parts[0]);
                    int a = Integer.parseInt(parts[1]);
                    int nB = Integer.parseInt(parts[2]);
                    int C1x = Integer.parseInt(parts[3]);
                    int C1y = Integer.parseInt(parts[4]);
                    int C2x = Integer.parseInt(parts[5]);
                    int C2y = Integer.parseInt(parts[6]);

                    System.out.println("Received C1: (" + C1x + "," + C1y + ")");
                    System.out.println("Received C2: (" + C2x + "," + C2y + ")");

                    // Compute Pm = C2 - nB * C1
                    int[] nBC1 = scalarMultiplication(nB, new int[] { C1x, C1y }, p, a);
                    int[] Pm = pointSubtraction(new int[] { C2x, C2y }, nBC1, p, a);

                    System.out.println("Decrypted Message (Pm): (" + Pm[0] + "," + Pm[1] + ")");
                }

                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Elliptic Curve Point Subtraction
    public static int[] pointSubtraction(int[] P, int[] Q, int p, int a) {
        int[] negQ = { Q[0], (p - Q[1]) % p };
        return pointAddition(P, negQ, p, a);
    }

    // Modular Inverse
    public static int modInverse(int x, int p) {
        return BigInteger.valueOf(x).modInverse(BigInteger.valueOf(p)).intValue();
    }

    // Reuse functions from Client
    public static int[] pointAddition(int[] P, int[] Q, int p, int a) {
        if (P[0] == -1 && P[1] == -1)
            return Q;
        if (Q[0] == -1 && Q[1] == -1)
            return P;

        int lambda;
        if (P[0] == Q[0] && P[1] == Q[1]) {
            lambda = ((3 * P[0] * P[0] + a) * modInverse(2 * P[1], p)) % p;
        } else {
            lambda = ((Q[1] - P[1]) * modInverse(Q[0] - P[0], p)) % p;
        }

        int Rx = (lambda * lambda - P[0] - Q[0]) % p;
        if (Rx < 0)
            Rx += p;

        int Ry = (lambda * (P[0] - Rx) - P[1]) % p;
        if (Ry < 0)
            Ry += p;

        return new int[] { Rx, Ry };
    }

    public static int[] scalarMultiplication(int k, int[] P, int p, int a) {
        int[] result = { -1, -1 };
        int[] base = P;

        while (k > 0) {
            if ((k & 1) == 1)
                result = pointAddition(result, base, p, a);
            base = pointAddition(base, base, p, a);
            k >>= 1;
        }
        return result;
    }
}
