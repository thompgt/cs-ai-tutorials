# Operating Systems Concepts

**Domain:** `systems`
**Level:** Beginner / Intermediate
**Prerequisites:** basic Python (loops, functions, classes), basic familiarity
with the `threading` module is helpful but not required — it's explained
from scratch.

## Summary

Every program you run shares a machine with dozens of others, all fighting
over the same CPU cores, the same finite RAM, and the same disk — and yet
they (mostly) don't crash into each other. This tutorial is a guided tour of
the operating system machinery that makes that possible. Starting from a
plain-English "OS as hotel manager" analogy, it works through **processes
and threads** (the units of execution and the process lifecycle), **CPU
scheduling** (implementing and comparing FCFS, SJF, Round Robin, and a
multilevel feedback queue on a shared workload, with real computed waiting
and turnaround times and Gantt-chart visuals), **memory management and
virtual memory** (paging, address translation, and a from-scratch
comparison of FIFO, LRU, and Optimal page replacement on a reference string
that reproduces Bélády's anomaly), **synchronization** (a real,
reproducible race condition in Python's `threading` module, its fix with
locks, a live deadlock demonstration, and two resolution strategies —
lock ordering and the Banker's algorithm), and a lighter conceptual pass
over **file systems** (inodes, allocation strategies, and a small simulated
allocator). Every algorithm is implemented and run — not just described —
so the numbers you see (fault counts, waiting times, deadlock/no-deadlock)
come from actually executing the code in this repo.

## Learning objectives

- Explain the process lifecycle (new → ready → running → waiting →
  terminated), the process control block, and why a context switch has
  real, measurable cost.
- Implement and compare FCFS, SJF, Round Robin, and multilevel feedback
  queue CPU scheduling on the same workload, and correctly compute average
  waiting time, turnaround time, and response time from a Gantt chart.
- Explain paging and virtual-to-physical address translation, and implement
  FIFO, LRU, and Optimal (Bélády) page replacement, reproducing Bélády's
  anomaly on a real reference string.
- Reproduce a genuine race condition with Python `threading`, fix it with a
  `Lock`, and state the formal mutual-exclusion requirements a correct
  solution must satisfy.
- State the four necessary conditions for deadlock, trigger a real deadlock
  between two threads, and resolve it with lock ordering and with the
  Banker's algorithm (implemented and run against a textbook allocation
  matrix).
- Describe the tradeoffs between contiguous, linked, and indexed file
  allocation and what an inode actually stores.
- Know where each of these mechanisms shows up in real operating systems
  (Linux CFS, the Windows/Linux virtual memory subsystem, database lock
  managers) and what their practical limitations are.

## Contents

- `tutorial.ipynb` — theory, visuals, and implementation

## References

- Silberschatz, Galvin & Gagne, *Operating System Concepts*, 10th ed.,
  Wiley.
- Tanenbaum & Bos, *Modern Operating Systems*, 4th ed., Pearson.
- Bélády, Nelson & Shedler (1969), *An Anomaly in Space-Time Characteristics
  of Certain Programs Running in a Paging Machine*, CACM.
- Dijkstra (1965), *Cooperating Sequential Processes* (mutual exclusion,
  the origin of the semaphore).
- Coffman, Elphick & Shoshani (1971), *System Deadlocks*, ACM Computing
  Surveys (the four necessary conditions).
- CPython docs, [`threading` — Thread-based
  parallelism](https://docs.python.org/3/library/threading.html) and the
  [Global Interpreter Lock](https://docs.python.org/3/glossary.html#term-global-interpreter-lock).
- Documentation for the Linux [Completely Fair
  Scheduler](https://docs.kernel.org/scheduler/sched-design-CFS.html).
