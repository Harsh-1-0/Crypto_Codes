import java.lang.reflect.Array;
import java.util.*;

public class MD5 {
    public static List<String> charToHex(String message) {
        List<String> hexVal = new ArrayList<>();
        for (char c : message.toCharArray()) {
            String hex = Integer.toHexString(c);
            hexVal.add(hex);
        }
        return hexVal;
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the string to be hashed: ");

        String message = sc.nextLine();

        int messageLengthBits = message.length() * 8;
        int paddingLengthBits = -(messageLengthBits + 64) % 512 + 512;

        System.out.println("Padding length in bits: " + paddingLengthBits);

        int paddingLengthBytes = paddingLengthBits / 8;
        System.out.println("Padding length in bytes: " + paddingLengthBytes);

        List<String> hexVal = charToHex(message);

        // Append 0x80 (10000000 in binary)
        hexVal.add("80");

        // Append zeros
        for (int i = 1; i < paddingLengthBytes; i++) {
            hexVal.add("00");
        }

        long messageLengthBitsLong = (long) message.length() * 8;

        List<String> lenBits = new ArrayList<>();
        for (int i = 0; i < 8; i++) {
            lenBits.add(String.format("%02x", (messageLengthBitsLong) & 0xFF));
            messageLengthBitsLong >>= 8;
        }
        Collections.reverse(lenBits);
        hexVal.addAll(lenBits);
        for (int i = 0; i < 16; i++) {
            System.out.print(i + " ");
            for (int j = 0; j < 4; j++) {
                System.out.print(hexVal.get(i * 4 + j) + " ");
            }
            System.out.println();
        }

    }
}