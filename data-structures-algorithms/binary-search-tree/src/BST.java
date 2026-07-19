import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * A textbook, unbalanced Binary Search Tree over ints.
 *
 * Supports insert, search, delete, and in-order traversal, and reports its
 * own height and node count so a driver program (or a notebook, via
 * subprocess) can measure real tree shape rather than a simulated one.
 *
 * Height convention: an empty tree has height -1, a single node has
 * height 0. (Some texts use "number of nodes on the longest root-to-leaf
 * path" instead, which is this value + 1 -- we use edge-count here and say
 * so explicitly, since the convention affects the exact numbers reported.)
 */
public class BST {

    private static class Node {
        int value;
        Node left, right;

        Node(int value) {
            this.value = value;
        }
    }

    private Node root;
    private int size = 0;

    /** Insert value into the tree. Duplicates are ignored (no-op). */
    public void insert(int value) {
        root = insert(root, value);
    }

    private Node insert(Node node, int value) {
        if (node == null) {
            size++;
            return new Node(value);
        }
        if (value < node.value) {
            node.left = insert(node.left, value);
        } else if (value > node.value) {
            node.right = insert(node.right, value);
        }
        // value == node.value: duplicate, ignore
        return node;
    }

    /** Return true if value is present in the tree. */
    public boolean search(int value) {
        Node cur = root;
        while (cur != null) {
            if (value == cur.value) return true;
            cur = value < cur.value ? cur.left : cur.right;
        }
        return false;
    }

    /** Delete value from the tree, if present. No-op if absent. */
    public void delete(int value) {
        root = delete(root, value);
    }

    private Node delete(Node node, int value) {
        if (node == null) return null;

        if (value < node.value) {
            node.left = delete(node.left, value);
        } else if (value > node.value) {
            node.right = delete(node.right, value);
        } else {
            // Found the node to delete. Three cases:

            // Case 1: leaf (no children) -- just remove it.
            if (node.left == null && node.right == null) {
                size--;
                return null;
            }

            // Case 2: exactly one child -- splice the child up in the
            // parent's place.
            if (node.left == null) {
                size--;
                return node.right;
            }
            if (node.right == null) {
                size--;
                return node.left;
            }

            // Case 3: two children -- replace this node's value with its
            // in-order successor (the smallest value in the right
            // subtree), then delete that successor from the right
            // subtree instead. The successor has at most a right child
            // (it's the leftmost node of node.right), so that recursive
            // delete always lands back in case 1 or case 2.
            Node successor = node.right;
            while (successor.left != null) {
                successor = successor.left;
            }
            node.value = successor.value;
            node.right = delete(node.right, successor.value);
        }
        return node;
    }

    /** In-order traversal: visits values in ascending sorted order. */
    public List<Integer> inOrder() {
        List<Integer> out = new ArrayList<>();
        inOrder(root, out);
        return out;
    }

    private void inOrder(Node node, List<Integer> out) {
        if (node == null) return;
        inOrder(node.left, out);
        out.add(node.value);
        inOrder(node.right, out);
    }

    /** Height in edges: empty tree = -1, single node = 0. */
    public int height() {
        return height(root);
    }

    private int height(Node node) {
        if (node == null) return -1;
        return 1 + Math.max(height(node.left), height(node.right));
    }

    public int size() {
        return size;
    }

    /**
     * Reads one command per line from stdin until EOF:
     *   I <v>   insert v
     *   D <v>   delete v
     *   S <v>   search v (prints "FOUND <v>" or "NOT_FOUND <v>")
     * After all commands are consumed, prints final stats:
     *   INORDER: <space-separated values>
     *   HEIGHT: <h>
     *   COUNT: <n>
     */
    public static void main(String[] args) {
        BST tree = new BST();
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();
            if (line.isEmpty()) continue;
            String[] parts = line.split("\\s+");
            char op = Character.toUpperCase(parts[0].charAt(0));
            int value = Integer.parseInt(parts[1]);

            switch (op) {
                case 'I':
                    tree.insert(value);
                    break;
                case 'D':
                    tree.delete(value);
                    break;
                case 'S':
                    System.out.println((tree.search(value) ? "FOUND " : "NOT_FOUND ") + value);
                    break;
                default:
                    throw new IllegalArgumentException("Unknown command: " + line);
            }
        }
        scanner.close();

        StringBuilder inorderLine = new StringBuilder("INORDER:");
        for (int v : tree.inOrder()) {
            inorderLine.append(' ').append(v);
        }
        System.out.println(inorderLine);
        System.out.println("HEIGHT: " + tree.height());
        System.out.println("COUNT: " + tree.size());

        // Dump the exact tree shape (preorder: value, left child, right
        // child, NULL for "no child") so a caller can reconstruct and draw
        // the real tree, not a simulated one.
        System.out.println("STRUCTURE:");
        tree.printStructure(tree.root);
    }

    private void printStructure(Node node) {
        if (node == null) return;
        String leftStr = node.left == null ? "NULL" : Integer.toString(node.left.value);
        String rightStr = node.right == null ? "NULL" : Integer.toString(node.right.value);
        System.out.println(node.value + " " + leftStr + " " + rightStr);
        printStructure(node.left);
        printStructure(node.right);
    }
}
