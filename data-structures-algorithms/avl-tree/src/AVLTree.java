import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * AVL tree: a self-balancing binary search tree.
 *
 * Every node stores its subtree height. After each insert or delete, the
 * tree walks back up from the changed node and, at any node whose balance
 * factor (left subtree height minus right subtree height) leaves the
 * range {-1, 0, 1}, performs a rotation (single or double) to restore it.
 * This keeps the tree's height within ~1.44 * log2(n) at all times, which
 * guarantees O(log n) worst-case search/insert/delete.
 *
 * A plain (unbalanced) BST insert is included alongside it so the two can
 * be compared head-to-head on the same input from one program.
 *
 * Modes (first CLI arg selects the mode; remaining args or stdin supply
 * whitespace-separated integer keys to insert, in order):
 *
 *   avl     - build an AVL tree, print final height and total rotations.
 *   bst     - build a plain unbalanced BST, print final height (rotations=0).
 *   trace   - build an AVL tree one key at a time, printing the rotation
 *             type (if any) and a full serialization of the tree after
 *             every single insert, so a driver can reconstruct "before"
 *             and "after" snapshots around any specific rotation.
 *   heights - build an AVL tree and a plain BST from the same insertion
 *             sequence simultaneously, printing both trees' heights after
 *             every insert (one JVM invocation instead of one per n).
 */
public class AVLTree {

    // ---- AVL node and core balancing machinery ----------------------------

    static class Node {
        int key;
        int height;
        Node left, right;

        Node(int key) {
            this.key = key;
            this.height = 1;
        }
    }

    /** Total number of single rotations performed so far (a double/LR or RL
     *  rotation is two single rotations, so it counts as 2). */
    static int rotationCount = 0;

    /** Rotation type applied by the most recent insert/delete call that
     *  rebalanced something: "LL", "RR", "LR", "RL", or "NONE". */
    static String lastRotationType = "NONE";

    static int height(Node n) {
        return n == null ? 0 : n.height;
    }

    static int balanceFactor(Node n) {
        return n == null ? 0 : height(n.left) - height(n.right);
    }

    static void updateHeight(Node n) {
        n.height = 1 + Math.max(height(n.left), height(n.right));
    }

    /** Rotate the subtree rooted at y to the right; x = y.left becomes the
     *  new subtree root. Used to fix left-heavy (balance factor > 1) nodes. */
    static Node rotateRight(Node y) {
        Node x = y.left;
        Node t2 = x.right;

        x.right = y;
        y.left = t2;

        updateHeight(y);
        updateHeight(x);
        rotationCount++;
        return x;
    }

    /** Rotate the subtree rooted at x to the left; y = x.right becomes the
     *  new subtree root. Used to fix right-heavy (balance factor < -1) nodes. */
    static Node rotateLeft(Node x) {
        Node y = x.right;
        Node t2 = y.left;

        y.left = x;
        x.right = t2;

        updateHeight(x);
        updateHeight(y);
        rotationCount++;
        return y;
    }

    // ---- AVL insert ---------------------------------------------------

    static Node insert(Node node, int key) {
        if (node == null) return new Node(key);

        if (key < node.key) {
            node.left = insert(node.left, key);
        } else if (key > node.key) {
            node.right = insert(node.right, key);
        } else {
            return node; // duplicate keys are ignored
        }

        updateHeight(node);
        int bf = balanceFactor(node);

        // Left-left case: left subtree is heavy and the new key went further left.
        if (bf > 1 && key < node.left.key) {
            lastRotationType = "LL";
            return rotateRight(node);
        }
        // Right-right case: right subtree is heavy and the new key went further right.
        if (bf < -1 && key > node.right.key) {
            lastRotationType = "RR";
            return rotateLeft(node);
        }
        // Left-right case: left subtree is heavy but the new key went right of it.
        if (bf > 1 && key > node.left.key) {
            lastRotationType = "LR";
            node.left = rotateLeft(node.left);
            return rotateRight(node);
        }
        // Right-left case: right subtree is heavy but the new key went left of it.
        if (bf < -1 && key < node.right.key) {
            lastRotationType = "RL";
            node.right = rotateRight(node.right);
            return rotateLeft(node);
        }

        return node;
    }

    // ---- AVL delete ---------------------------------------------------

    static Node minValueNode(Node n) {
        while (n.left != null) n = n.left;
        return n;
    }

    static Node delete(Node node, int key) {
        if (node == null) return null;

        if (key < node.key) {
            node.left = delete(node.left, key);
        } else if (key > node.key) {
            node.right = delete(node.right, key);
        } else {
            if (node.left == null || node.right == null) {
                node = (node.left != null) ? node.left : node.right;
            } else {
                Node successor = minValueNode(node.right);
                node.key = successor.key;
                node.right = delete(node.right, successor.key);
            }
        }

        if (node == null) return null;

        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1 && balanceFactor(node.left) >= 0) {
            lastRotationType = "LL";
            return rotateRight(node);
        }
        if (bf > 1 && balanceFactor(node.left) < 0) {
            lastRotationType = "LR";
            node.left = rotateLeft(node.left);
            return rotateRight(node);
        }
        if (bf < -1 && balanceFactor(node.right) <= 0) {
            lastRotationType = "RR";
            return rotateLeft(node);
        }
        if (bf < -1 && balanceFactor(node.right) > 0) {
            lastRotationType = "RL";
            node.right = rotateRight(node.right);
            return rotateLeft(node);
        }

        return node;
    }

    /** Parenthesized serialization: key(left,right), empty for a null child.
     *  e.g. "5(3(1,4),8(,9))". Used by the "trace" mode so a Python driver
     *  can rebuild and draw the tree at any point in the insertion sequence. */
    static String serialize(Node n) {
        if (n == null) return "";
        return n.key + "(" + serialize(n.left) + "," + serialize(n.right) + ")";
    }

    // ---- Plain (unbalanced) BST, for comparison ------------------------

    static class BSTNode {
        int key;
        BSTNode left, right;

        BSTNode(int key) {
            this.key = key;
        }
    }

    static BSTNode bstInsert(BSTNode node, int key) {
        if (node == null) return new BSTNode(key);
        if (key < node.key) node.left = bstInsert(node.left, key);
        else if (key > node.key) node.right = bstInsert(node.right, key);
        return node;
    }

    static int bstHeight(BSTNode n) {
        return n == null ? 0 : 1 + Math.max(bstHeight(n.left), bstHeight(n.right));
    }

    // ---- main / CLI -----------------------------------------------------

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("usage: AVLTree <avl|bst|trace> [values...]  (values read from stdin if omitted)");
            System.exit(1);
        }

        String mode = args[0];
        List<Integer> values = new ArrayList<>();
        if (args.length > 1) {
            for (int i = 1; i < args.length; i++) values.add(Integer.parseInt(args[i]));
        } else {
            Scanner sc = new Scanner(System.in);
            while (sc.hasNextInt()) values.add(sc.nextInt());
        }

        switch (mode) {
            case "avl": {
                Node root = null;
                rotationCount = 0;
                for (int v : values) root = insert(root, v);
                System.out.println("mode=avl");
                System.out.println("n=" + values.size());
                System.out.println("height=" + height(root));
                System.out.println("rotations=" + rotationCount);
                break;
            }
            case "bst": {
                BSTNode root = null;
                for (int v : values) root = bstInsert(root, v);
                System.out.println("mode=bst");
                System.out.println("n=" + values.size());
                System.out.println("height=" + bstHeight(root));
                System.out.println("rotations=0");
                break;
            }
            case "heights": {
                // Build an AVL tree and a plain BST incrementally, inserting the
                // same sequence into both, and report both heights after every
                // single insert -- one JVM invocation instead of one per n.
                Node avlRoot = null;
                BSTNode bstRoot = null;
                int step = 0;
                for (int v : values) {
                    avlRoot = insert(avlRoot, v);
                    bstRoot = bstInsert(bstRoot, v);
                    step++;
                    System.out.println("STEP " + step + " N=" + step
                            + " AVL_HEIGHT=" + height(avlRoot)
                            + " BST_HEIGHT=" + bstHeight(bstRoot));
                }
                break;
            }
            case "trace": {
                Node root = null;
                rotationCount = 0;
                for (int v : values) {
                    int before = rotationCount;
                    lastRotationType = "NONE";
                    root = insert(root, v);
                    int stepRotations = rotationCount - before;
                    String type = stepRotations > 0 ? lastRotationType : "NONE";
                    System.out.println("INSERT " + v + " ROTATIONS=" + stepRotations
                            + " TYPE=" + type + " TREE=" + serialize(root));
                }
                System.out.println("FINAL height=" + height(root) + " rotations=" + rotationCount);
                break;
            }
            default:
                System.err.println("unknown mode: " + mode);
                System.exit(1);
        }
    }
}
