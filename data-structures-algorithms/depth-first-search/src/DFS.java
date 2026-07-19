import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

/**
 * Depth-first search over an adjacency-list graph, in both the classic
 * recursive form and an explicit-stack iterative form that simulates the
 * same call stack by hand. Both variants:
 *
 *   - record CLRS-style discover/finish timestamps for every vertex,
 *   - classify every edge as TREE, BACK, FORWARD, or CROSS,
 *   - report whether a BACK edge was found (a directed back edge always
 *     means a cycle exists -- see the tutorial's "Going deeper" section),
 *   - visit the whole graph (not just one component), starting at the
 *     requested start vertex and then sweeping any remaining unvisited
 *     vertices in index order, exactly like CLRS's DFS(G) procedure.
 *
 * Input (stdin), whitespace/newline separated integers:
 *   V E directed start
 *   u1 v1
 *   u2 v2
 *   ...
 *   uE vE
 *
 *   V        = number of vertices, labeled 0..V-1
 *   E        = number of edges that follow
 *   directed = 1 for a directed graph, 0 for undirected
 *   start    = vertex to begin the traversal at
 *
 * Build: javac DFS.java
 * Run:   java DFS < graph.txt
 */
public class DFS {

    static final int WHITE = 0, GRAY = 1, BLACK = 2;

    static class Graph {
        final int V;
        final boolean directed;
        final List<List<Integer>> adj;

        Graph(int V, boolean directed) {
            this.V = V;
            this.directed = directed;
            adj = new ArrayList<>();
            for (int i = 0; i < V; i++) adj.add(new ArrayList<>());
        }

        void addEdge(int u, int v) {
            adj.get(u).add(v);
            if (!directed) adj.get(v).add(u);
        }
    }

    static class DFSResult {
        List<Integer> order = new ArrayList<>();
        int[] discover;
        int[] finish;
        List<String> edgeClassifications = new ArrayList<>();
        boolean cycleFound = false;
    }

    // ---- Recursive DFS ----------------------------------------------------

    static DFSResult recursiveDFS(Graph g, int start) {
        DFSResult result = new DFSResult();
        int[] color = new int[g.V];
        int[] parent = new int[g.V];
        Arrays.fill(parent, -1);
        result.discover = new int[g.V];
        result.finish = new int[g.V];
        int[] time = {0};

        recursiveVisit(g, start, color, parent, result, time);
        for (int u = 0; u < g.V; u++) {
            if (color[u] == WHITE) recursiveVisit(g, u, color, parent, result, time);
        }
        return result;
    }

    private static void recursiveVisit(Graph g, int u, int[] color, int[] parent,
                                        DFSResult result, int[] time) {
        color[u] = GRAY;
        time[0]++;
        result.discover[u] = time[0];
        result.order.add(u);

        for (int v : g.adj.get(u)) {
            if (!g.directed && v == parent[u]) {
                // Skip exactly one occurrence of the edge back to our parent --
                // it's the same undirected edge we just walked down, not a new one.
                parent[u] = -2;
                continue;
            }
            if (color[v] == WHITE) {
                result.edgeClassifications.add(u + " " + v + " TREE");
                parent[v] = u;
                recursiveVisit(g, v, color, parent, result, time);
            } else if (color[v] == GRAY) {
                result.edgeClassifications.add(u + " " + v + " BACK");
                result.cycleFound = true;
            } else if (g.directed) {
                // BLACK neighbor: only meaningful (and only possible) for directed
                // graphs -- see the parenthesis theorem in the tutorial.
                if (result.discover[u] < result.discover[v]) {
                    result.edgeClassifications.add(u + " " + v + " FORWARD");
                } else {
                    result.edgeClassifications.add(u + " " + v + " CROSS");
                }
            }
        }

        color[u] = BLACK;
        time[0]++;
        result.finish[u] = time[0];
    }

    // ---- Iterative DFS (explicit stack) ------------------------------------

    /** One activation-record frame: which vertex, and how far through its
     *  adjacency list we've gotten. Mirrors exactly what the recursive
     *  version's call stack holds implicitly. */
    static class Frame {
        final int vertex;
        int adjIndex;
        Frame(int vertex) {
            this.vertex = vertex;
            this.adjIndex = 0;
        }
    }

    static DFSResult iterativeDFS(Graph g, int start) {
        DFSResult result = new DFSResult();
        int[] color = new int[g.V];
        int[] parent = new int[g.V];
        Arrays.fill(parent, -1);
        result.discover = new int[g.V];
        result.finish = new int[g.V];
        int[] time = {0};

        iterativeVisit(g, start, color, parent, result, time);
        for (int u = 0; u < g.V; u++) {
            if (color[u] == WHITE) iterativeVisit(g, u, color, parent, result, time);
        }
        return result;
    }

    private static void iterativeVisit(Graph g, int start, int[] color, int[] parent,
                                        DFSResult result, int[] time) {
        ArrayDeque<Frame> stack = new ArrayDeque<>();

        color[start] = GRAY;
        time[0]++;
        result.discover[start] = time[0];
        result.order.add(start);
        stack.push(new Frame(start));

        while (!stack.isEmpty()) {
            Frame frame = stack.peek();
            int u = frame.vertex;
            List<Integer> neighbors = g.adj.get(u);

            if (frame.adjIndex < neighbors.size()) {
                int v = neighbors.get(frame.adjIndex);
                frame.adjIndex++;

                if (!g.directed && v == parent[u]) {
                    parent[u] = -2;
                    continue;
                }
                if (color[v] == WHITE) {
                    result.edgeClassifications.add(u + " " + v + " TREE");
                    parent[v] = u;
                    color[v] = GRAY;
                    time[0]++;
                    result.discover[v] = time[0];
                    result.order.add(v);
                    stack.push(new Frame(v));
                } else if (color[v] == GRAY) {
                    result.edgeClassifications.add(u + " " + v + " BACK");
                    result.cycleFound = true;
                } else if (g.directed) {
                    if (result.discover[u] < result.discover[v]) {
                        result.edgeClassifications.add(u + " " + v + " FORWARD");
                    } else {
                        result.edgeClassifications.add(u + " " + v + " CROSS");
                    }
                }
            } else {
                color[u] = BLACK;
                time[0]++;
                result.finish[u] = time[0];
                stack.pop();
            }
        }
    }

    // ---- I/O ----------------------------------------------------------------

    static Graph readGraph(Scanner sc, int[] startOut) {
        int V = sc.nextInt();
        int E = sc.nextInt();
        boolean directed = sc.nextInt() == 1;
        startOut[0] = sc.nextInt();
        Graph g = new Graph(V, directed);
        for (int i = 0; i < E; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            g.addEdge(u, v);
        }
        return g;
    }

    static void printResult(DFSResult r) {
        StringBuilder order = new StringBuilder("ORDER:");
        for (int v : r.order) order.append(" ").append(v);
        System.out.println(order);

        StringBuilder discover = new StringBuilder("DISCOVER:");
        for (int u = 0; u < r.discover.length; u++) discover.append(" ").append(u).append("=").append(r.discover[u]);
        System.out.println(discover);

        StringBuilder finish = new StringBuilder("FINISH:");
        for (int u = 0; u < r.finish.length; u++) finish.append(" ").append(u).append("=").append(r.finish[u]);
        System.out.println(finish);

        for (String e : r.edgeClassifications) System.out.println("EDGE " + e);

        System.out.println("CYCLE: " + r.cycleFound);
    }

    public static void main(String[] args) {
        // Optional first CLI arg selects which variant(s) to run: "recursive",
        // "iterative", or "both" (default). Useful for isolating the recursive
        // version on a deliberately deep input where it's expected to blow the
        // call stack, without the iterative run never getting a chance to execute.
        String mode = args.length > 0 ? args[0] : "both";

        Scanner sc = new Scanner(System.in);
        int[] startOut = new int[1];
        Graph g = readGraph(sc, startOut);
        int start = startOut[0];

        System.out.println("GRAPH vertices=" + g.V + " directed=" + g.directed + " start=" + start);

        if (mode.equals("recursive") || mode.equals("both")) {
            System.out.println("--- RECURSIVE DFS ---");
            DFSResult recursiveResult = recursiveDFS(g, start);
            printResult(recursiveResult);
        }

        if (mode.equals("iterative") || mode.equals("both")) {
            System.out.println("--- ITERATIVE DFS (explicit stack) ---");
            DFSResult iterativeResult = iterativeDFS(g, start);
            printResult(iterativeResult);
        }
    }
}
