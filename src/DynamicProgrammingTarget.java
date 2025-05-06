import java.util.Random;

public class DynamicProgrammingTarget {

    public static void shootDP(int n, int hidingSpot) {
        int moveCount = 0;
        boolean directionRight = true;
        int left = 1;
        int right = n;

        System.out.println("Target is hiding at position: " + hidingSpot);
        System.out.println("Dynamic Programming Search:");

        while (true) {
            if (directionRight) {
                for (int i = left; i <= right; i++) {
                    moveCount++;
                    System.out.println("Shot " + moveCount + ": Shooting at " + i + ", Hiding at " + hidingSpot);
                    if (i == hidingSpot) {
                        System.out.println("Target hit at position " + hidingSpot + "!");
                        System.out.println("Total shots taken (DP): " + moveCount);
                        return;
                    }
                    hidingSpot = moveTarget(hidingSpot, n);
                }
            } else {
                for (int i = right; i >= left; i--) {
                    moveCount++;
                    System.out.println("Shot " + moveCount + ": Shooting at " + i + ", Hiding at " + hidingSpot);
                    if (i == hidingSpot) {
                        System.out.println("Target hit at position " + hidingSpot + "!");
                        System.out.println("Total shots taken (DP): " + moveCount);
                        return;
                    }
                    hidingSpot = moveTarget(hidingSpot, n);
                }
            }

            directionRight = !directionRight;
        }
    }

    public static int moveTarget(int current, int n) {
        if (current == 1) return 2;
        if (current == n) return n - 1;
        return (Math.random() < 0.5) ? current - 1 : current + 1;
    }

    public static void main(String[] args) {
        int n = 8;
        Random rand = new Random();
        int hidingSpot = rand.nextInt(n) + 1;

        shootDP(n, hidingSpot);
    }
}
