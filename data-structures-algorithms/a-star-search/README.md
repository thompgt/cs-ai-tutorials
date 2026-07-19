# A* Search

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays/lists); helpful (not
required) to have seen Dijkstra's algorithm first, since A* is presented as
a direct extension of it
**Language:** C++ (real, compiled, and executed — see `src/`)

## Summary

A* search ranks frontier cells by $f(n) = g(n) + h(n)$ — the real distance
walked so far, $g(n)$, plus a heuristic estimate of remaining distance to
the goal, $h(n)$ — instead of Dijkstra's algorithm, which ranks purely by
$g(n)$. This tutorial opens with a plain-English "video-game character
pathfinding toward a flag" analogy and a hand-traced 5x5 grid example
before introducing any notation, then formally defines **admissibility**
and **consistency**, sketch-proves that A* with an admissible heuristic is
guaranteed to find the same optimal-cost path Dijkstra would, and shows the
clean formal fact that **A* with $h \equiv 0$ is exactly Dijkstra's
algorithm**. All of this is confirmed against a **real, compiled C++
implementation** (`src/astar.cpp`) that runs both A* and plain Dijkstra
(via a single boolean flag) on identical grids — the side-by-side
"which cells got explored" visualization and the nodes-expanded-vs-grid-size
plot are built entirely from real measurements of the compiled binary, not
simulated numbers.

## Learning objectives

- Explain why ranking frontier nodes by $f(n) = g(n) + h(n)$ instead of
  $g(n)$ alone lets A* reach the goal while examining far fewer cells than
  Dijkstra.
- Define **admissibility** ($h(n) \le h^*(n)$, never overestimating true
  remaining distance) and **consistency** ($h(n) \le \text{cost}(n, n') +
  h(n')$), and sketch-prove that an admissible heuristic guarantees A*
  finds the same optimal-cost path as Dijkstra.
- State and understand the clean formal connection: A* with $h(n) = 0$ for
  all $n$ is literally Dijkstra's algorithm, not just an analogy to it.
- Compile and run a real C++ implementation of both A* and Dijkstra on
  identical grids, and confirm from real program output that A* explores
  substantially fewer cells for the same optimal-cost path.
- Know A*'s real-world tradeoffs: heuristic quality/cost as the entire
  source of its speed advantage, memory usage vs. memory-bounded
  alternatives like IDA*, and weighted A* as a deliberate, common
  optimality-for-speed tradeoff.

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough with a
  hand-traced grid example, formal admissibility/consistency proofs,
  visuals (real explored-cells comparison, real nodes-expanded-vs-size
  plot), real compiled-C++ implementation and measurements, use cases,
  limitations & debates
- `src/astar.cpp` — the real C++ implementation (A* and Dijkstra in one
  search function, 4-directional movement, Manhattan-distance heuristic),
  compiled and run from the notebook. Build manually with:
  `g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ src/astar.cpp -o src/astar.exe`

## References

- Hart, P. E., Nilsson, N. J., & Raphael, B. *A Formal Basis for the
  Heuristic Determination of Minimum Cost Paths*, IEEE Transactions on
  Systems Science and Cybernetics, 1968.
- Russell, S. & Norvig, P. *Artificial Intelligence: A Modern Approach*,
  heuristic search chapter.
- `src/astar.cpp` in this tutorial's folder — the real, compiled
  implementation used for every measurement in the notebook.
