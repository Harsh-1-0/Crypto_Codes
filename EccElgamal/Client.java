import java.io.*;
import java.math.BigInteger;
import java.net.*;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String SERVER_ADDRESS = "localhost";
        int PORT = 5000;

        // Taking user input
        System.out.print("Enter prime field (p): ");
        int p = scanner.nextInt();
        System.out.print("Enter curve coefficient a: ");
        int a = scanner.nextInt();
        System.out.print("Enter curve coefficient b: ");
        int b = scanner.nextInt();
        System.out.print("Enter base point G (x y): ");
        int Gx = scanner.nextInt(), Gy = scanner.nextInt();
        System.out.print("Enter your private key (nB): ");
        int nB = scanner.nextInt();
        System.out.print("Enter message point Pm (x y): ");
        int Pmx = scanner.nextInt(), Pmy = scanner.nextInt();
        System.out.print("Enter random integer (k): ");
        int k = scanner.nextInt();

        // Compute public key PB = nB * G
        int[] PB = scalarMultiplication(nB, new int[] { Gx, Gy }, p, a);
        System.out.println("Public Key (PB): (" + PB[0] + "," + PB[1] + ")");

        // Compute C1 = k * G
        int[] C1 = scalarMultiplication(k, new int[] { Gx, Gy }, p, a);
        System.out.println("C1: (" + C1[0] + "," + C1[1] + ")");

        // Compute C2 = Pm + k * PB
        int[] kPB = scalarMultiplication(k, PB, p, a);
        int[] C2 = pointAddition(new int[] { Pmx, Pmy }, kPB, p, a);
        System.out.println("C2: (" + C2[0] + "," + C2[1] + ")");

        // Send data over socket
        try (Socket socket = new Socket(SERVER_ADDRESS, PORT);
                PrintWriter writer = new PrintWriter(socket.getOutputStream(), true)) {

            writer.println(p + "," + a + "," + nB + "," + C1[0] + "," + C1[1] + "," + C2[0] + "," + C2[1]);
        } catch (IOException e) {
            e.printStackTrace();
        }

        scanner.close();
    }

    // Elliptic Curve Point Addition
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

    // Elliptic Curve Scalar Multiplication
    public static int[] scalarMultiplication(int k, int[] P, int p, int a) {
        int[] result = { -1, -1 };
        int[] base = P;

        while (k > 0) {
            if ((k & 1) == 1) {
                result = pointAddition(result, base, p, a);
            }
            base = pointAddition(base, base, p, a);
            k >>= 1;
        }
        return result;
    }

    // Modular Inverse
    public static int modInverse(int x, int p) {
        return BigInteger.valueOf(x).modInverse(BigInteger.valueOf(p)).intValue();
    }
}
