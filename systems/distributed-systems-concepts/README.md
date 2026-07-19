# Distributed Systems: Core Concepts

**Domain:** `systems`
**Level:** Intermediate
**Prerequisites:** comfortable reading Python (classes, loops, basic `threading`),
general familiarity with client/server terms (server, request, network), no
prior distributed-systems background assumed

## Summary

Why does keeping multiple computers agreeing on "the truth" turn out to be
one of the hardest problems in computer science — harder than any single
algorithm you'd write for one machine? This tutorial builds the answer from
the ground up through four runnable simulations, each written from scratch
in plain Python (`threading` + message-passing over queues, with injected
delay/loss — no real sockets or multiple machines required).

You'll see, with real printed output: (1) why partial failure and no shared
clock make single-machine intuitions fail, illustrated with a bank-transfer
scenario; (2) a real toy replicated key-value store where injecting a
network partition forces a live choice between the C and the A in **CAP**;
(3) **Lamport timestamps** and **vector clocks** correctly ordering (or
correctly flagging as concurrent) events pulled from simulated, independently-
running processes; (4) a simplified but real **Raft-style leader election**
across 5 simulated nodes with randomized election timeouts, term numbers,
and majority quorum, run multiple times to show both a clean election and a
split vote being resolved; and (5) a **consistent hashing** ring compared
numerically against naive mod-N hashing to show why consistent hashing keeps
key remapping minimal when nodes join or leave a cluster.

## Learning objectives

- Explain why distributed systems are fundamentally harder than single-node
  systems: partial failure, no shared memory, no global clock, and an
  unreliable network, and connect each to a concrete failure scenario.
- State the CAP theorem formally, prove (by construction) why a partition
  forces a C-vs-A choice, and demonstrate the tradeoff live in a simulated
  replicated key-value store.
- Implement Lamport timestamps and vector clocks, use them to establish a
  causal (happens-before) order over simulated distributed events, and
  explain what vector clocks can detect that Lamport timestamps cannot
  (true concurrency).
- Explain why consensus (e.g. leader election, replicated log agreement) is
  necessary in a distributed system and implement a simplified Raft leader
  election: randomized timeouts, terms, and majority quorum voting.
- Implement consistent hashing and quantify — with real computed
  percentages — how much less key remapping it causes than naive mod-N
  hashing when the cluster is resized.
- Describe where each concept shows up in real systems (DynamoDB, Cassandra,
  etcd/Raft, Google Spanner, load balancers) and the tradeoffs/known
  criticisms of each model.

## Contents

- `tutorial.ipynb` — theory, visuals, and implementation (self-contained;
  all simulations run with Python's standard library plus numpy/matplotlib/
  networkx)

## References

- Lamport, L. (1978). *Time, Clocks, and the Ordering of Events in a
  Distributed System.* Communications of the ACM, 21(7).
- Fidge, C. J. (1988). *Timestamps in Message-Passing Systems That Preserve
  the Partial Ordering.* / Mattern, F. (1989). *Virtual Time and Global
  States of Distributed Systems.* (independent origins of vector clocks)
- Gilbert, S., & Lynch, N. (2002). *Brewer's Conjecture and the Feasibility
  of Consistent, Available, Partition-Tolerant Web Services.* ACM SIGACT
  News, 33(2). (formal proof of CAP)
- Ongaro, D., & Ousterhout, J. (2014). *In Search of an Understandable
  Consensus Algorithm (Raft).* USENIX ATC. Also see [raft.github.io](https://raft.github.io/).
- Karger, D. et al. (1997). *Consistent Hashing and Random Trees.* ACM STOC.
- DeCandia, G. et al. (2007). *Dynamo: Amazon's Highly Available Key-value
  Store.* SOSP. (eventual consistency and vector clocks in production)
- Corbett, J. et al. (2012). *Spanner: Google's Globally-Distributed
  Database.* OSDI. (TrueTime and strong consistency at scale)
