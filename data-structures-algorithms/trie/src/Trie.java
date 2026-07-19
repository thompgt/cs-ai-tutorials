// Trie (prefix tree) with instrumentation, plus a naive linear-scan
// baseline used purely for benchmarking comparisons in the tutorial.
//
// Build: javac Trie.java
// Run:   java Trie < input.txt
//
// Input protocol (whitespace-delimited, one token/line as noted):
//   <W>                     number of words to insert
//   word_1 .. word_W        one per line
//   <Q>                     number of queries
//   CMD arg                 one per line, Q times
//
// Supported CMDs:
//   SEARCH <word>   exact match -- true iff <word> was inserted and marked end-of-word
//   PREFIX <word>   true iff any inserted word starts with <word>
//   COUNT  <word>   number of inserted words that start with <word>
//   SCAN   <word>   naive baseline: linear scan over all inserted words counting
//                    how many start with <word> (same semantics as COUNT, different algorithm)
//   DUMP            print the trie's node/edge structure for visualization
//
// Every query line prints: CMD arg result nanos
// DUMP prints a DUMP_START ... DUMP_END block of "id parentId char isEnd" rows.

import java.util.*;
import java.io.*;

public class Trie {

    static class Node {
        Map<Character, Node> children = new TreeMap<>();
        boolean isEndOfWord = false;
        // wordsBelow = how many complete words exist in the subtree rooted here,
        // including this node itself if it is an end-of-word. Maintained
        // incrementally on insert so countWordsWithPrefix is O(L), not O(L + subtree size).
        int wordsBelow = 0;
    }

    private final Node root = new Node();

    /** Insert a word into the trie, walking/creating one node per character. O(L). */
    public void insert(String word) {
        Node cur = root;
        cur.wordsBelow++;
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            cur = cur.children.computeIfAbsent(c, k -> new Node());
            cur.wordsBelow++;
        }
        cur.isEndOfWord = true;
    }

    /** Walk the trie following `word`'s characters; return the node reached, or null if the path breaks. */
    private Node walk(String word) {
        Node cur = root;
        for (int i = 0; i < word.length(); i++) {
            cur = cur.children.get(word.charAt(i));
            if (cur == null) return null;
        }
        return cur;
    }

    /** Exact-match search: does `word` exist as a complete inserted word? O(L). */
    public boolean search(String word) {
        Node n = walk(word);
        return n != null && n.isEndOfWord;
    }

    /** Prefix search: does any inserted word start with `prefix`? O(L). */
    public boolean startsWith(String prefix) {
        return walk(prefix) != null;
    }

    /** Count how many inserted words start with `prefix`. O(L) thanks to the wordsBelow counters. */
    public int countWordsWithPrefix(String prefix) {
        Node n = walk(prefix);
        return n == null ? 0 : n.wordsBelow;
    }

    // ---- Naive baseline for benchmarking: scan every stored word, check startsWith. O(n * L). ----
    static int naiveScanCount(List<String> allWords, String prefix) {
        int count = 0;
        for (String w : allWords) {
            if (w.startsWith(prefix)) count++;
        }
        return count;
    }

    // ---- DUMP: assign each node a stable id via DFS and print parent/char/isEnd rows. ----
    private void dump(PrintStream out) {
        out.println("DUMP_START");
        int[] nextId = {0};
        Map<Node, Integer> ids = new IdentityHashMap<>();
        ids.put(root, nextId[0]++);
        out.println(ids.get(root) + " -1 ROOT " + (root.isEndOfWord ? 1 : 0));
        dumpRec(root, ids, nextId, out);
        out.println("DUMP_END");
    }

    private void dumpRec(Node node, Map<Node, Integer> ids, int[] nextId, PrintStream out) {
        for (Map.Entry<Character, Node> e : node.children.entrySet()) {
            Node child = e.getValue();
            int id = nextId[0]++;
            ids.put(child, id);
            out.println(id + " " + ids.get(node) + " " + e.getKey() + " " + (child.isEndOfWord ? 1 : 0));
            dumpRec(child, ids, nextId, out);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintStream out = System.out;

        int w = Integer.parseInt(br.readLine().trim());
        List<String> words = new ArrayList<>(w);
        Trie trie = new Trie();

        long insertStart = System.nanoTime();
        for (int i = 0; i < w; i++) {
            String word = br.readLine().trim();
            words.add(word);
            trie.insert(word);
        }
        long insertNanos = System.nanoTime() - insertStart;
        out.println("INSERT_ALL " + w + " " + insertNanos);

        int q = Integer.parseInt(br.readLine().trim());
        for (int i = 0; i < q; i++) {
            String line = br.readLine();
            if (line == null) break;
            line = line.trim();
            if (line.isEmpty()) continue;

            if (line.equals("DUMP")) {
                trie.dump(out);
                continue;
            }

            int sp = line.indexOf(' ');
            String cmd = line.substring(0, sp);
            String arg = line.substring(sp + 1);

            long start, nanos;
            switch (cmd) {
                case "SEARCH":
                    start = System.nanoTime();
                    boolean found = trie.search(arg);
                    nanos = System.nanoTime() - start;
                    out.println("SEARCH " + arg + " " + found + " " + nanos);
                    break;
                case "PREFIX":
                    start = System.nanoTime();
                    boolean has = trie.startsWith(arg);
                    nanos = System.nanoTime() - start;
                    out.println("PREFIX " + arg + " " + has + " " + nanos);
                    break;
                case "COUNT":
                    start = System.nanoTime();
                    int cnt = trie.countWordsWithPrefix(arg);
                    nanos = System.nanoTime() - start;
                    out.println("COUNT " + arg + " " + cnt + " " + nanos);
                    break;
                case "SCAN":
                    start = System.nanoTime();
                    int scanCnt = naiveScanCount(words, arg);
                    nanos = System.nanoTime() - start;
                    out.println("SCAN " + arg + " " + scanCnt + " " + nanos);
                    break;
                default:
                    out.println("ERROR unknown_command " + cmd);
            }
        }
    }
}
