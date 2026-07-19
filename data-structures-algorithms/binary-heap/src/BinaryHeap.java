import java.util.Arrays;
import java.util.Scanner;

/**
 * An array-backed binary min-heap (a priority queue where the smallest
 * value is always served first).
 *
 * The heap is a *complete* binary tree stored flat in an array: for a node
 * at index i, its children live at indices 2i+1 and 2i+2, and its parent
 * lives at index (i-1)/2 (integer division). No pointers are needed -- the
 * tree shape is implied entirely by array position.
 *
 * Supports insert (append + sift-up), extractMin (swap-last-to-root +
 * sift-down), peek (O(1)), and a static heapify(int[]) that builds a heap
 * from an unsorted array in-place in O(n), not O(n log n). Every sift-up /
 * sift-down step is instrumented with comparison and swap counters, and
 * main() times whichever operation the caller asked for, so a driver
 * program (or a notebook, via subprocess) measures real behavior rather
 * than a simulated one.
 */
public class BinaryHeap {

    private int[] heap;
    private int size;

    private static long comparisons = 0;
    private static long swaps = 0;

    public BinaryHeap(int capacity) {
        this.heap = new int[Math.max(capacity, 1)];
        this.size = 0;
    }

    public static void resetStats() {
        comparisons = 0;
        swaps = 0;
    }

    public static long getComparisons() {
        return comparisons;
    }

    public static long getSwaps() {
        return swaps;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    /** Return the minimum element without removing it. O(1): it's always the root. */
    public int peek() {
        if (size == 0) throw new IllegalStateException("heap is empty");
        return heap[0];
    }

    /** Insert a value: append at the end, then bubble it up until the heap property holds. */
    public void insert(int value) {
        ensureCapacity(size + 1);
        heap[size] = value;
        size++;
        siftUp(size - 1);
    }

    // Bubble the element at index i up toward the root while it is smaller
    // than its parent. Bounded by the height of the tree: O(log n).
    private void siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            comparisons++;
            if (heap[parent] <= heap[i]) {
                break; // heap property restored
            }
            swap(parent, i);
            i = parent;
        }
    }

    /** Remove and return the minimum element, restoring the heap property. */
    public int extractMin() {
        if (size == 0) throw new IllegalStateException("heap is empty");
        int min = heap[0];
        size--;
        heap[0] = heap[size];
        heap[size] = 0; // not required for correctness, just tidiness
        if (size > 0) {
            siftDown(0);
        }
        return min;
    }

    // Bubble the element at index i down toward the leaves, always swapping
    // with the smaller child, until the heap property holds. Bounded by
    // the height of the tree: O(log n).
    private void siftDown(int i) {
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < size) {
                comparisons++;
                if (heap[left] < heap[smallest]) {
                    smallest = left;
                }
            }
            if (right < size) {
                comparisons++;
                if (heap[right] < heap[smallest]) {
                    smallest = right;
                }
            }
            if (smallest == i) {
                break; // heap property restored
            }
            swap(i, smallest);
            i = smallest;
        }
    }

    private void swap(int i, int j) {
        if (i == j) return;
        int tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;
        swaps++;
    }

    private void ensureCapacity(int needed) {
        if (needed <= heap.length) return;
        heap = Arrays.copyOf(heap, Math.max(needed, heap.length * 2));
    }

    /** Return a copy of the array, truncated to the current logical size. */
    public int[] toArray() {
        return Arrays.copyOf(heap, size);
    }

    /**
     * Build a min-heap from an unsorted array in-place, in O(n) time (see
     * the tutorial's "Going deeper" section for the sum-of-heights proof).
     *
     * The trick: start at the last non-leaf node (index n/2 - 1, since
     * everything after that is a leaf and trivially already a valid
     * one-node heap) and sift each node down, working *backwards* to the
     * root. By the time we sift down node i, both of its subtrees are
     * already valid heaps, so one sift-down per node is enough.
     */
    public static BinaryHeap heapify(int[] values) {
        BinaryHeap h = new BinaryHeap(values.length);
        h.heap = Arrays.copyOf(values, values.length);
        h.size = values.length;
        for (int i = values.length / 2 - 1; i >= 0; i--) {
            h.siftDown(i);
        }
        return h;
    }

    // ---- Driver ------------------------------------------------------

    /**
     * Usage: java BinaryHeap <mode>, with input on stdin. Modes:
     *
     *   trace     Reads one command per line until EOF:
     *               I <v>   insert v, then prints "STATE: <array>"
     *               E       extract-min, prints "EXTRACT <v>" then "STATE: <array>"
     *               P       peek, prints "PEEK <v>"
     *             Used to hand-trace individual inserts/extracts for diagrams.
     *
     *   inserts   Reads whitespace-separated ints from stdin, builds a heap
     *             by inserting them one at a time into an initially empty
     *             heap (the O(n log n) build strategy), and prints timing +
     *             instrumentation stats for the build.
     *
     *   heapify   Same input format, but builds the heap with a single
     *             heapify() call (the O(n) build strategy). Prints the same
     *             stats format so the two strategies are directly comparable.
     *
     *   heapsort  Same input format: heapify(), then repeatedly extractMin
     *             until empty, collecting results in ascending order. Prints
     *             "sorted: <array>" plus stats -- demonstrates heapsort
     *             (build-heap + n extract-mins) as a correct, real sort.
     */
    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("usage: java BinaryHeap <trace|inserts|heapify|heapsort>");
            System.exit(1);
        }
        String mode = args[0];
        Scanner scanner = new Scanner(System.in);

        switch (mode) {
            case "trace":
                runTrace(scanner);
                break;
            case "inserts":
                runInserts(scanner);
                break;
            case "heapify":
                runHeapify(scanner);
                break;
            case "heapsort":
                runHeapsort(scanner);
                break;
            default:
                System.err.println("unknown mode: " + mode);
                System.exit(1);
        }
        scanner.close();
    }

    private static void runTrace(Scanner scanner) {
        BinaryHeap h = new BinaryHeap(16);
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();
            if (line.isEmpty()) continue;
            String[] parts = line.split("\\s+");
            char op = Character.toUpperCase(parts[0].charAt(0));
            switch (op) {
                case 'I': {
                    int value = Integer.parseInt(parts[1]);
                    h.insert(value);
                    System.out.println("STATE: " + arrayToString(h.toArray()));
                    break;
                }
                case 'E': {
                    int min = h.extractMin();
                    System.out.println("EXTRACT " + min);
                    System.out.println("STATE: " + arrayToString(h.toArray()));
                    break;
                }
                case 'P': {
                    System.out.println("PEEK " + h.peek());
                    break;
                }
                default:
                    throw new IllegalArgumentException("Unknown command: " + line);
            }
        }
    }

    private static int[] readValues(Scanner scanner) {
        java.util.List<Integer> values = new java.util.ArrayList<>();
        while (scanner.hasNextInt()) {
            values.add(scanner.nextInt());
        }
        int[] arr = new int[values.size()];
        for (int i = 0; i < arr.length; i++) arr[i] = values.get(i);
        return arr;
    }

    private static void runInserts(Scanner scanner) {
        int[] values = readValues(scanner);
        resetStats();
        BinaryHeap h = new BinaryHeap(values.length);
        long start = System.nanoTime();
        for (int v : values) {
            h.insert(v);
        }
        long end = System.nanoTime();
        printStats("heap", h.toArray(), start, end);
    }

    private static void runHeapify(Scanner scanner) {
        int[] values = readValues(scanner);
        resetStats();
        long start = System.nanoTime();
        BinaryHeap h = heapify(values);
        long end = System.nanoTime();
        printStats("heap", h.toArray(), start, end);
    }

    private static void runHeapsort(Scanner scanner) {
        int[] values = readValues(scanner);
        resetStats();
        long start = System.nanoTime();
        BinaryHeap h = heapify(values);
        int[] sorted = new int[values.length];
        for (int i = 0; i < sorted.length; i++) {
            sorted[i] = h.extractMin();
        }
        long end = System.nanoTime();
        printStats("sorted", sorted, start, end);
    }

    private static void printStats(String label, int[] arr, long startNanos, long endNanos) {
        long micros = (endNanos - startNanos) / 1000;
        System.out.println(label + ": " + arrayToString(arr));
        System.out.println("n=" + arr.length);
        System.out.println("comparisons=" + comparisons);
        System.out.println("swaps=" + swaps);
        System.out.println("microseconds=" + micros);
    }

    private static String arrayToString(int[] arr) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < arr.length; i++) {
            sb.append(arr[i]);
            if (i + 1 < arr.length) sb.append(' ');
        }
        return sb.toString();
    }
}
