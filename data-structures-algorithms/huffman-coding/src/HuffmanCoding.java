import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.TreeMap;

/**
 * Huffman coding: build a binary prefix code from character frequencies,
 * then use it to compress ("encode") and losslessly decompress ("decode")
 * a piece of text.
 *
 * The core idea: repeatedly take the two LEAST-frequent nodes in a min-heap
 * and merge them into a new internal node (frequency = sum of the two).
 * Symbols that get merged early (rare ones) end up deep in the resulting
 * tree -> long codes. Symbols merged late (common ones) end up shallow ->
 * short codes. Because every original symbol sits at a LEAF, no symbol's
 * code can ever be a prefix of another symbol's code -- that's what makes
 * the encoded bitstream unambiguously decodable with no delimiters.
 */
public class HuffmanCoding {

    /** A node in the Huffman tree. Leaves hold a real symbol; internal
     *  nodes hold only a combined frequency and two children. */
    static class Node implements Comparable<Node> {
        final char symbol;      // meaningless for internal nodes
        final long freq;
        final boolean isLeaf;
        final Node left;
        final Node right;
        // insertion order is used only as a deterministic tie-breaker so
        // that ties between equal frequencies don't depend on heap internals
        final long order;

        Node(char symbol, long freq, long order) {
            this.symbol = symbol;
            this.freq = freq;
            this.isLeaf = true;
            this.left = null;
            this.right = null;
            this.order = order;
        }

        Node(Node left, Node right, long order) {
            this.symbol = '\0';
            this.freq = left.freq + right.freq;
            this.isLeaf = false;
            this.left = left;
            this.right = right;
            this.order = order;
        }

        @Override
        public int compareTo(Node other) {
            if (this.freq != other.freq) {
                return Long.compare(this.freq, other.freq);
            }
            // deterministic tie-break: earlier-created node is "smaller"
            return Long.compare(this.order, other.order);
        }
    }

    /** Step 1: count how often each character appears. */
    static Map<Character, Long> countFrequencies(String text) {
        Map<Character, Long> freqs = new TreeMap<>();
        for (int i = 0; i < text.length(); i++) {
            char c = text.charAt(i);
            freqs.merge(c, 1L, Long::sum);
        }
        return freqs;
    }

    /**
     * Step 2: build the Huffman tree bottom-up.
     * Repeatedly pull the two lowest-frequency nodes off a min-heap and
     * merge them into a new parent node, pushing the parent back in.
     * After n-1 merges (n = number of distinct symbols), one node remains:
     * the root of the Huffman tree.
     */
    static Node buildTree(Map<Character, Long> freqs) {
        if (freqs.isEmpty()) {
            throw new IllegalArgumentException("cannot build a Huffman tree for empty input");
        }

        PriorityQueue<Node> heap = new PriorityQueue<>();
        long order = 0;
        for (Map.Entry<Character, Long> e : freqs.entrySet()) {
            heap.add(new Node(e.getKey(), e.getValue(), order++));
        }

        // Special case: exactly one distinct symbol. A single leaf can't
        // be its own root-to-leaf path of length > 0, so we force a
        // 1-bit code by giving it an artificial sibling-free parent.
        if (heap.size() == 1) {
            Node only = heap.poll();
            return new Node(only, new Node('\0', 0, order++), order);
        }

        while (heap.size() > 1) {
            Node a = heap.poll(); // least frequent
            Node b = heap.poll(); // second least frequent
            heap.add(new Node(a, b, order++));
        }
        return heap.poll();
    }

    /**
     * Step 3: walk the tree root -> leaf, recording the path (0 = left,
     * 1 = right) as a bit string. That path IS the symbol's code.
     */
    static Map<Character, String> buildCodes(Node root) {
        Map<Character, String> codes = new TreeMap<>();
        buildCodesHelper(root, new StringBuilder(), codes);
        return codes;
    }

    private static void buildCodesHelper(Node node, StringBuilder path, Map<Character, String> codes) {
        if (node.isLeaf) {
            // A lone real symbol (the single-distinct-character case) could
            // reach here with an empty path; guard against a 0-length code.
            codes.put(node.symbol, path.length() == 0 ? "0" : path.toString());
            return;
        }
        path.append('0');
        buildCodesHelper(node.left, path, codes);
        path.setLength(path.length() - 1);

        path.append('1');
        buildCodesHelper(node.right, path, codes);
        path.setLength(path.length() - 1);
    }

    /** Encode text into a bit string using the given code table. */
    static String encode(String text, Map<Character, String> codes) {
        StringBuilder bits = new StringBuilder();
        for (int i = 0; i < text.length(); i++) {
            bits.append(codes.get(text.charAt(i)));
        }
        return bits.toString();
    }

    /**
     * Decode a bit string back into text by walking the tree bit by bit
     * from the root; every time a leaf is reached, emit its symbol and
     * restart from the root. This only works unambiguously because the
     * code is prefix-free (Step 3 guarantees every real symbol is a leaf).
     */
    static String decode(String bits, Node root) {
        StringBuilder text = new StringBuilder();
        Node current = root;
        // Degenerate single-symbol tree: root's children are leaf/leaf,
        // real symbol is root.left. Handle generically below regardless.
        for (int i = 0; i < bits.length(); i++) {
            current = (bits.charAt(i) == '0') ? current.left : current.right;
            if (current.isLeaf) {
                text.append(current.symbol);
                current = root;
            }
        }
        return text.toString();
    }

    static String readAllStdin() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in, StandardCharsets.UTF_8));
        StringBuilder sb = new StringBuilder();
        int ch;
        while ((ch = reader.read()) != -1) {
            sb.append((char) ch);
        }
        // Trim exactly one trailing newline that shells/redirection often add,
        // but keep the rest of the text (including internal newlines) intact.
        if (sb.length() > 0 && sb.charAt(sb.length() - 1) == '\n') {
            sb.setLength(sb.length() - 1);
        }
        if (sb.length() > 0 && sb.charAt(sb.length() - 1) == '\r') {
            sb.setLength(sb.length() - 1);
        }
        return sb.toString();
    }

    public static void main(String[] args) throws IOException {
        String text;
        if (args.length > 0) {
            text = String.join(" ", args);
        } else {
            text = readAllStdin();
        }

        if (text.isEmpty()) {
            System.out.println("no input text provided; nothing to encode");
            return;
        }

        Map<Character, Long> freqs = countFrequencies(text);
        Node root = buildTree(freqs);
        Map<Character, String> codes = buildCodes(root);

        String encoded = encode(text, codes);
        String decoded = decode(encoded, root);

        System.out.println("=== Frequencies & codes ===");
        // Print only the real symbols that occur in the input -- buildCodes()
        // may also assign a code to an artificial placeholder leaf used
        // internally for the single-distinct-symbol special case.
        for (Map.Entry<Character, Long> e : freqs.entrySet()) {
            System.out.println(describeChar(e.getKey()) + "  freq=" + e.getValue()
                    + "  code=" + codes.get(e.getKey()));
        }

        System.out.println("\n=== Encoded output (bits) ===");
        System.out.println(encoded);

        System.out.println("\n=== Decoded output ===");
        System.out.println(decoded);

        boolean matches = decoded.equals(text);
        System.out.println("\n=== Correctness check ===");
        System.out.println("decoded == original: " + matches);
        if (!matches) {
            throw new IllegalStateException("round-trip FAILED: decoded text does not match original");
        }

        long originalBits = (long) text.length() * 8; // fixed-width 8-bit ASCII baseline
        long encodedBits = encoded.length();
        double ratio = (double) encodedBits / (double) originalBits;
        double avgBitsPerChar = (double) encodedBits / (double) text.length();

        System.out.println("\n=== Compression stats ===");
        System.out.println("distinct symbols   = " + freqs.size());
        System.out.println("original length    = " + text.length() + " chars");
        System.out.println("original size bits  = " + originalBits + " (8 bits/char fixed-width)");
        System.out.println("encoded size bits   = " + encodedBits);
        System.out.println("avg bits/char       = " + String.format("%.4f", avgBitsPerChar));
        System.out.println("compression ratio   = " + String.format("%.4f", ratio)
                + " (encoded/original, lower is better)");
        System.out.println("space saved         = " + String.format("%.2f", (1 - ratio) * 100) + "%");
    }

    private static String describeChar(char c) {
        if (c == '\n') return "'\\n'";
        if (c == '\r') return "'\\r'";
        if (c == '\t') return "'\\t'";
        if (c == ' ') return "' ' (space)";
        return "'" + c + "'";
    }
}
