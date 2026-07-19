import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * Breadth-first search over an undirected graph, adjacency-list
 * representation.
 *
 * Reads a graph and a source vertex, runs BFS, and reports:
 *   - each vertex's distance (in edges) from the source, or -1 if
 *     unreachable
 *   - the total number of vertices visited
 *   - the wall-clock time of the traversal itself (excludes I/O and
 *     graph construction), in microseconds
 *
 * so a driver program (or a notebook, via subprocess) can measure real
 * BFS behavior on real graphs rather than a simulated stand-in.
 *
 * Input format (stdin):
 *   line 1:        N M        (vertex count, edge count; vertices are 0..N-1)
 *   next M lines:  u v        (an undirected edge between u and v)
 *
 * Source vertex: args[0] if provided, else 0.
 *
 * Output format (stdout):
 *   DIST: <v> <distance>      one line per vertex, in vertex order
 *   VISITED: <count>
 *   TIME_MICROS: <t>
 */
public class BFS {

    private final int n;
    private final List<List<Integer>> adj;

    public BFS(int n) {
        this.n = n;
        adj = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }
    }

    public void addEdge(int u, int v) {
        adj.get(u).add(v);
        adj.get(v).add(u);
    }

    /**
     * Runs BFS from source and returns the distance array (dist[v] = -1
     * if v is unreachable from source).
     *
     * The key correctness detail: a vertex is marked visited (dist set)
     * the moment it is *enqueued*, not when it is later dequeued. If we
     * waited until dequeue time to mark it, the same vertex could be
     * discovered again -- and enqueued again -- by every other neighbor
     * that reaches it before its first copy is dequeued, since none of
     * those neighbors would yet see it as visited. That blows up the
     * queue with duplicate entries (in the worst case, exponentially
     * many) and breaks the O(V+E) bound. Marking at enqueue time
     * guarantees each vertex is enqueued exactly once.
     */
    public int[] bfs(int source) {
        int[] dist = new int[n];
        java.util.Arrays.fill(dist, -1);

        ArrayDeque<Integer> queue = new ArrayDeque<>();
        dist[source] = 0;          // mark visited immediately on discovery
        queue.add(source);

        while (!queue.isEmpty()) {
            int u = queue.poll();
            for (int v : adj.get(u)) {
                if (dist[v] == -1) {           // not yet discovered
                    dist[v] = dist[u] + 1;     // mark visited *here*, at enqueue time
                    queue.add(v);
                }
            }
        }
        return dist;
    }

    public static void main(String[] args) {
        int source = args.length > 0 ? Integer.parseInt(args[0]) : 0;

        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int m = scanner.nextInt();

        BFS graph = new BFS(n);
        for (int i = 0; i < m; i++) {
            int u = scanner.nextInt();
            int v = scanner.nextInt();
            graph.addEdge(u, v);
        }
        scanner.close();

        long start = System.nanoTime();
        int[] dist = graph.bfs(source);
        long elapsedMicros = (System.nanoTime() - start) / 1000;

        int visited = 0;
        StringBuilder out = new StringBuilder();
        for (int v = 0; v < n; v++) {
            out.append("DIST: ").append(v).append(' ').append(dist[v]).append('\n');
            if (dist[v] != -1) visited++;
        }
        out.append("VISITED: ").append(visited).append('\n');
        out.append("TIME_MICROS: ").append(elapsedMicros).append('\n');
        System.out.print(out);
    }
}
