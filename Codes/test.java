
import java.util.*;

public class test {

    public static int round1(int b, int c, int d) {
        return ((b & c) | (~b & d));
    }

    public static int round2(int b, int c, int d) {
        return ((b & d) | (c & ~d));
    }

    public static int round3(int b, int c, int d) {
        return (b ^ c ^ d);
    }

    public static int round4(int b, int c, int d) {
        return (c ^ (b | ~d));
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter three integers: ");
        int b = (int) Long.parseUnsignedLong(sc.next(), 16);
        int c = (int) Long.parseUnsignedLong(sc.next(), 16);
        int d = (int) Long.parseUnsignedLong(sc.next(), 16);
        System.out.println("Round 1: " + Integer.toHexString(round1(b, c, d)));
        System.out.println("Round 2: " + Integer.toHexString(round2(b, c, d)));
        System.out.println("Round 3: " + Integer.toHexString(round3(b, c, d)));
        System.out.println("Round 4: " + Integer.toHexString(round4(b, c, d)));
    }
}