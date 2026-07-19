// A* search and plain Dijkstra (A* with h=0) on a 2D grid with obstacles,
// with 4-directional movement (see README/notebook for why: it keeps the
// Manhattan-distance heuristic exactly admissible and consistent).
//
// Reads a grid from stdin in the format:
//   rows cols
//   rows lines of cols characters each: '.' = free, '#' = obstacle
//   start_row start_col
//   goal_row goal_col
//
// Runs BOTH algorithms on the same grid and prints, for each:
//   - whether a path was found
//   - the path cost (number of steps, since edge weight = 1)
//   - the path itself (as "r,c" cells, space-separated)
//   - the set of expanded (closed-set) cells, as "r,c" pairs
//   - nodes expanded (closed-set size)
//   - wall-clock time in microseconds
//
// Build:  g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ astar.cpp -o astar
// Run:    ./astar < grid.txt

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <chrono>
#include <limits>
#include <string>
#include <sstream>
#include <algorithm>

struct Cell {
    int r, c;
};

struct Node {
    double f;
    int r, c;
    bool operator>(const Node& other) const { return f > other.f; }
};

// Manhattan distance -- the admissible & consistent heuristic for
// 4-directional movement (every move costs exactly 1, and Manhattan
// distance never overestimates the number of 4-directional steps needed).
static double manhattan(int r1, int c1, int r2, int c2) {
    return std::abs(r1 - r2) + std::abs(c1 - c2);
}

struct SearchResult {
    bool found = false;
    double cost = 0.0;
    std::vector<Cell> path;
    std::vector<Cell> expanded; // closed-set order
    long long nodesExpanded = 0;
    long long microseconds = 0;
};

// Generic best-first search: heuristic() returns 0 for Dijkstra, Manhattan
// distance for A*. Everything else is identical -- this is the "A* with
// h=0 IS Dijkstra" fact made literal in code, not just asserted in prose.
SearchResult search(const std::vector<std::string>& grid, Cell start, Cell goal,
                     bool useHeuristic) {
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    std::vector<std::vector<double>> g(rows, std::vector<double>(rows > 0 ? cols : 0,
                                        std::numeric_limits<double>::infinity()));
    std::vector<std::vector<bool>> closed(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<Cell>> parent(rows, std::vector<Cell>(cols, {-1, -1}));

    auto heuristic = [&](int r, int c) -> double {
        if (!useHeuristic) return 0.0;
        return manhattan(r, c, goal.r, goal.c);
    };

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open;

    g[start.r][start.c] = 0.0;
    open.push({heuristic(start.r, start.c), start.r, start.c});

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    SearchResult result;
    auto t0 = std::chrono::high_resolution_clock::now();

    while (!open.empty()) {
        Node cur = open.top();
        open.pop();

        if (closed[cur.r][cur.c]) continue; // stale entry, skip
        closed[cur.r][cur.c] = true;
        result.expanded.push_back({cur.r, cur.c});

        if (cur.r == goal.r && cur.c == goal.c) {
            result.found = true;
            result.cost = g[cur.r][cur.c];
            Cell walk = goal;
            while (!(walk.r == start.r && walk.c == start.c)) {
                result.path.push_back(walk);
                walk = parent[walk.r][walk.c];
            }
            result.path.push_back(start);
            std::reverse(result.path.begin(), result.path.end());
            break;
        }

        for (int d = 0; d < 4; d++) {
            int nr = cur.r + dr[d];
            int nc = cur.c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            if (grid[nr][nc] == '#') continue;
            if (closed[nr][nc]) continue;

            double tentativeG = g[cur.r][cur.c] + 1.0; // unit edge weight
            if (tentativeG < g[nr][nc]) {
                g[nr][nc] = tentativeG;
                parent[nr][nc] = {cur.r, cur.c};
                double f = tentativeG + heuristic(nr, nc);
                open.push({f, nr, nc});
            }
        }
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    result.nodesExpanded = static_cast<long long>(result.expanded.size());
    result.microseconds = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    return result;
}

static void printResult(const std::string& label, const SearchResult& r) {
    std::cout << label << ".found=" << (r.found ? 1 : 0) << "\n";
    std::cout << label << ".cost=" << r.cost << "\n";
    std::cout << label << ".nodes_expanded=" << r.nodesExpanded << "\n";
    std::cout << label << ".microseconds=" << r.microseconds << "\n";

    std::cout << label << ".path=";
    for (size_t i = 0; i < r.path.size(); i++) {
        std::cout << r.path[i].r << "," << r.path[i].c;
        if (i + 1 < r.path.size()) std::cout << " ";
    }
    std::cout << "\n";

    std::cout << label << ".expanded=";
    for (size_t i = 0; i < r.expanded.size(); i++) {
        std::cout << r.expanded[i].r << "," << r.expanded[i].c;
        if (i + 1 < r.expanded.size()) std::cout << " ";
    }
    std::cout << "\n";
}

int main() {
    int rows, cols;
    if (!(std::cin >> rows >> cols)) return 1;
    std::cin.ignore();

    std::vector<std::string> grid(rows);
    for (int i = 0; i < rows; i++) {
        std::getline(std::cin, grid[i]);
        // Guard against short/blank lines from stray whitespace.
        while (static_cast<int>(grid[i].size()) < cols) grid[i] += '.';
    }

    Cell start{}, goal{};
    std::cin >> start.r >> start.c >> goal.r >> goal.c;

    SearchResult astarResult = search(grid, start, goal, /*useHeuristic=*/true);
    SearchResult dijkstraResult = search(grid, start, goal, /*useHeuristic=*/false);

    printResult("astar", astarResult);
    printResult("dijkstra", dijkstraResult);

    return 0;
}
