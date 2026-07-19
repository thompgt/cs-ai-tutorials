// Topological Sort: Kahn's algorithm (BFS/in-degree based) and the
// DFS-based method (reverse of finishing-time order), both with explicit
// cycle detection, instrumented with wall-clock timing.
//
// Input: a directed graph as an edge list read from stdin, one edge per
// line: "A B" meaning "A must happen before B" (an edge A -> B). Node
// labels are arbitrary whitespace-free tokens. Blank lines are ignored.
// A line with a single token declares an isolated node (no dependencies,
// no dependents).
//
// An optional single CLI argument, "asc" (default) or "desc", picks the
// tie-breaking rule Kahn's algorithm uses among nodes that simultaneously
// reach in-degree zero. Both are equally valid topological orders -- this
// exists to demonstrate that the result is generally NOT unique.
//
// Build:  javac TopologicalSort.java
// Run:    java TopologicalSort < graph.txt
//         java TopologicalSort desc < graph.txt
//
// Output: the order discovered by each method (or "CYCLE DETECTED" plus the
// set of nodes still stuck in a cycle), and the elapsed time in
// microseconds for each method.

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Set;

public class TopologicalSort {

    /** Result of a topological sort attempt: either a full order, or the set
     *  of nodes that could not be ordered because they sit on a cycle. */
    static final class Result {
        final List<String> order;      // valid topological order, or null if a cycle exists
        final Set<String> cycleNodes;  // non-empty iff order == null
        final long micros;             // wall-clock time for this method

        Result(List<String> order, Set<String> cycleNodes, long micros) {
            this.order = order;
            this.cycleNodes = cycleNodes;
            this.micros = micros;
        }

        boolean hasCycle() {
            return order == null;
        }
    }

    /** Directed graph as an adjacency map, built from an edge list.
     *  Preserves insertion order of nodes for deterministic tie-breaking. */
    static final class Graph {
        final Map<String, List<String>> adjacency = new LinkedHashMap<>();

        void addNode(String node) {
            adjacency.computeIfAbsent(node, k -> new ArrayList<>());
        }

        void addEdge(String from, String to) {
            addNode(from);
            addNode(to);
            adjacency.get(from).add(to);
        }

        int nodeCount() {
            return adjacency.size();
        }

        int edgeCount() {
            int total = 0;
            for (List<String> neighbors : adjacency.values()) total += neighbors.size();
            return total;
        }
    }

    /**
     * Kahn's algorithm: repeatedly remove a node with in-degree zero
     * (no remaining unprocessed prerequisites), append it to the order,
     * and decrement the in-degree of its neighbors.
     *
     * Tie-breaking: nodes with in-degree zero are held in a priority queue
     * ordered by the supplied comparator, so callers can force a specific
     * (still valid) ordering among ties to demonstrate non-uniqueness.
     */
    static Result kahn(Graph graph, Comparator<String> tieBreaker) {
        long start = System.nanoTime();

        Map<String, Integer> inDegree = new HashMap<>();
        for (String node : graph.adjacency.keySet()) inDegree.put(node, 0);
        for (List<String> neighbors : graph.adjacency.values()) {
            for (String to : neighbors) {
                inDegree.merge(to, 1, Integer::sum);
            }
        }

        PriorityQueue<String> ready = new PriorityQueue<>(tieBreaker);
        for (Map.Entry<String, Integer> e : inDegree.entrySet()) {
            if (e.getValue() == 0) ready.add(e.getKey());
        }

        List<String> order = new ArrayList<>();
        while (!ready.isEmpty()) {
            String node = ready.poll();
            order.add(node);
            for (String neighbor : graph.adjacency.get(node)) {
                int updated = inDegree.merge(neighbor, -1, Integer::sum);
                if (updated == 0) ready.add(neighbor);
            }
        }

        long elapsed = (System.nanoTime() - start) / 1000;

        if (order.size() != graph.nodeCount()) {
            // Whatever is left with nonzero in-degree is stuck in (or
            // downstream of) a cycle -- Kahn's algorithm reveals ALL of it,
            // not just one offending edge.
            Set<String> stuck = new LinkedHashSet<>();
            for (Map.Entry<String, Integer> e : inDegree.entrySet()) {
                if (e.getValue() > 0) stuck.add(e.getKey());
            }
            return new Result(null, stuck, elapsed);
        }
        return new Result(order, Collections.emptySet(), elapsed);
    }

    /**
     * DFS-based topological sort: run DFS from every node, record each
     * node's finishing time (when its recursion fully completes), and
     * return nodes in REVERSE order of finishing time.
     *
     * Cycle detection: a "gray" (currently on the recursion stack) node
     * reached again means a back edge, i.e. a cycle. We report the
     * back-edge node plus everything currently on the stack (the cycle
     * itself, since a node's ancestors on the stack are exactly the
     * "must happen before it" chain that closes the loop).
     */
    static Result dfsTopoSort(Graph graph) {
        long start = System.nanoTime();

        Set<String> visited = new HashSet<>();      // finished (black)
        Set<String> onStack = new LinkedHashSet<>(); // currently being explored (gray)
        Deque<String> finishOrder = new ArrayDeque<>();
        Set<String> cycleNodes = new LinkedHashSet<>();

        for (String start_node : graph.adjacency.keySet()) {
            if (!visited.contains(start_node)) {
                dfsVisit(graph, start_node, visited, onStack, finishOrder, cycleNodes);
            }
        }

        long elapsed = (System.nanoTime() - start) / 1000;

        if (!cycleNodes.isEmpty()) {
            return new Result(null, cycleNodes, elapsed);
        }

        // finishOrder was pushed in finishing order; reverse it.
        List<String> order = new ArrayList<>(finishOrder);
        Collections.reverse(order);
        return new Result(order, Collections.emptySet(), elapsed);
    }

    private static void dfsVisit(Graph graph, String node, Set<String> visited,
                                  Set<String> onStack, Deque<String> finishOrder,
                                  Set<String> cycleNodes) {
        visited.add(node);
        onStack.add(node);
        for (String neighbor : graph.adjacency.get(node)) {
            if (onStack.contains(neighbor)) {
                // Back edge -> cycle. Record everything currently on the
                // stack: that is precisely the chain of "must come before"
                // dependencies that loops back on itself.
                cycleNodes.addAll(onStack);
                cycleNodes.add(neighbor);
            } else if (!visited.contains(neighbor)) {
                dfsVisit(graph, neighbor, visited, onStack, finishOrder, cycleNodes);
            }
        }
        onStack.remove(node);
        finishOrder.addLast(node); // node "finishes" here
    }

    static Graph readGraph(BufferedReader reader) throws IOException {
        Graph graph = new Graph();
        String line;
        while ((line = reader.readLine()) != null) {
            line = line.trim();
            if (line.isEmpty() || line.startsWith("#")) continue;
            String[] parts = line.split("\\s+");
            if (parts.length == 1) {
                graph.addNode(parts[0]);
            } else if (parts.length >= 2) {
                graph.addEdge(parts[0], parts[1]);
            }
        }
        return graph;
    }

    static void printResult(String label, Result result) {
        System.out.println(label + ":");
        if (result.hasCycle()) {
            System.out.println("  CYCLE DETECTED - no valid topological order exists");
            System.out.println("  nodes involved in/blocked by cycle: " + result.cycleNodes);
        } else {
            System.out.println("  order: " + result.order);
        }
        System.out.println("  time_micros=" + result.micros);
    }

    public static void main(String[] args) throws IOException {
        String tieBreak = args.length >= 1 ? args[0] : "asc";
        Comparator<String> comparator = "desc".equals(tieBreak)
                ? Comparator.<String>naturalOrder().reversed()
                : Comparator.naturalOrder();

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        Graph graph = readGraph(reader);
        reader.close();

        System.out.println("n=" + graph.nodeCount());
        System.out.println("e=" + graph.edgeCount());

        Result kahnResult = kahn(graph, comparator);
        printResult("kahn", kahnResult);

        Result dfsResult = dfsTopoSort(graph);
        printResult("dfs", dfsResult);
    }
}
