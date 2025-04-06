import java.util.*;

public class OptimalBST {
    static class Node {
        int keyIndex;
        Node left, right;

        Node(int keyIndex) {
            this.keyIndex = keyIndex;
        }
    }

    public static void main(String[] args) {
        int[] keys = {10, 20, 30, 40}; // sorted keys
        double[] p = {0.1, 0.2, 0.4, 0.3}; // search probabilities

        int n = keys.length;
        double[][] cost = new double[n + 2][n + 2];
        int[][] root = new int[n + 1][n + 1];

        // Initialize cost[i][i-1] = 0 for i in [1, n+1]
        for (int i = 1; i <= n + 1; i++) {
            cost[i][i - 1] = 0;
        }

        // w[i][j] stores the sum of probabilities from i to j
        double[][] w = new double[n + 2][n + 2];

        for (int i = 1; i <= n; i++) {
            w[i][i] = p[i - 1];
            cost[i][i] = p[i - 1];
            root[i][i] = i;
        }

        for (int len = 2; len <= n; len++) {
            for (int i = 1; i <= n - len + 1; i++) {
                int j = i + len - 1;
                cost[i][j] = Double.MAX_VALUE;
                w[i][j] = w[i][j - 1] + p[j - 1];

                for (int r = i; r <= j; r++) {
                    double c = cost[i][r - 1] + cost[r + 1][j];
                    if (c < cost[i][j]) {
                        cost[i][j] = c;
                        root[i][j] = r;
                    }
                }
                cost[i][j] += w[i][j];
            }
        }

        Node rootNode = buildTree(root, keys, 1, n);
        System.out.println("1. Cost of tree: " + cost[1][n]);
        System.out.println("2. Root of tree: " + keys[root[1][n] - 1]);
        System.out.print("3. Tree structure: ");
        printTree(rootNode, keys);
    }

    static Node buildTree(int[][] root, int[] keys, int i, int j) {
        if (i > j) return null;

        int r = root[i][j];
        Node node = new Node(r);
        node.left = buildTree(root, keys, i, r - 1);
        node.right = buildTree(root, keys, r + 1, j);
        return node;
    }

    static void printTree(Node node, int[] keys) {
        if (node == null) {
            System.out.print("null ");
            return;
        }

        System.out.print(keys[node.keyIndex - 1] + " ( ");
        printTree(node.left, keys);
        printTree(node.right, keys);
        System.out.print(") ");
    }
}


