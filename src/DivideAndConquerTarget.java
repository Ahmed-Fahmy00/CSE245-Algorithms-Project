import java.util.Random;
import java.util.ArrayList;
import java.util.List;

public class DivideAndConquerTarget {

    public static int moveTarget(int current, int n) {
        if (current == 1) return 2;
        if (current == n) return n - 1;
        return (Math.random() < 0.5) ? current - 1 : current + 1;
    }

    public static List<Integer> generateDivideAndConquerOrder(int start, int end) {
        List<Integer> result = new ArrayList<>();
        if (start > end) return result;

        int mid = (start + end) / 2;
        result.add(mid);
        result.addAll(generateDivideAndConquerOrder(start, mid - 1));
        result.addAll(generateDivideAndConquerOrder(mid + 1, end));
        return result;
    }

    public static int shootDivideAndConquer(int n, int hidingSpot) {
        List<Integer> shotOrder = generateDivideAndConquerOrder(1, n);
        int totalShots = 0;

        System.out.println("Divide and Conquer Search:");
        while (true) {
            for (int shot : shotOrder) {
                totalShots++;
                System.out.println("Shot " + totalShots + ": Shooting at " + shot + ", Hiding at " + hidingSpot);

                if (shot == hidingSpot) {
                    System.out.println("Target hit at position " + hidingSpot + "!");
                    return totalShots;
                }

                hidingSpot = moveTarget(hidingSpot, n);
            }
        }
    }

    public static void main(String[] args) {
        int n = 8;
        Random rand = new Random();
        int hidingSpot = rand.nextInt(n) + 1;

        System.out.println("Target initially hiding at position: " + hidingSpot);
        int totalShots = shootDivideAndConquer(n, hidingSpot);
        System.out.println("Total shots taken (DAC): " + totalShots);
    }
}
