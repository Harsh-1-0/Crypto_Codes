import java.io.*;
import java.math.BigInteger;
import java.net.*;
import java.util.Scanner;

public class Eve {
    private static final int PORT = 5000;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter prime number (p): ");
        int p = scanner.nextInt();
        System.out.print("Enter generator (g): ");
        int g = scanner.nextInt();
        System.out.print("Enter Eve's private key (z): ");
        int z = scanner.nextInt();

        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Eve (MITM) is intercepting messages...");

            Socket aliceSocket = serverSocket.accept();
            System.out.println("Alice connected...");
            BufferedReader aliceReader = new BufferedReader(new InputStreamReader(aliceSocket.getInputStream()));
            PrintWriter aliceWriter = new PrintWriter(aliceSocket.getOutputStream(), true);

            Socket bobSocket = serverSocket.accept();
            System.out.println("Bob connected...");
            BufferedReader bobReader = new BufferedReader(new InputStreamReader(bobSocket.getInputStream()));
            PrintWriter bobWriter = new PrintWriter(bobSocket.getOutputStream(), true);

            String alicePublicKeyStr = aliceReader.readLine();
            BigInteger alicePublicKey = new BigInteger(alicePublicKeyStr);
            System.out.println("[Eve] Intercepted Alice's Public Key: " + alicePublicKey);

            BigInteger evePublicKey = BigInteger.valueOf(g).modPow(BigInteger.valueOf(z), BigInteger.valueOf(p));
            bobWriter.println(evePublicKey);
            System.out.println("[Eve] Sent Fake Public Key to Bob: " + evePublicKey);

            String bobPublicKeyStr = bobReader.readLine();
            BigInteger bobPublicKey = new BigInteger(bobPublicKeyStr);
            System.out.println("[Eve] Intercepted Bob's Public Key: " + bobPublicKey);

            aliceWriter.println(evePublicKey);
            System.out.println("[Eve] Sent Fake Public Key to Alice: " + evePublicKey);

            BigInteger sharedKeyAlice = alicePublicKey.modPow(BigInteger.valueOf(z), BigInteger.valueOf(p));
            BigInteger sharedKeyBob = bobPublicKey.modPow(BigInteger.valueOf(z), BigInteger.valueOf(p));

            System.out.println("[Eve] Shared Key with Alice: " + sharedKeyAlice);
            System.out.println("[Eve] Shared Key with Bob: " + sharedKeyBob);

            aliceSocket.close();
            bobSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        scanner.close();
    }
}
