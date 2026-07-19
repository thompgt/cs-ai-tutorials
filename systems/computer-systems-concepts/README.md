# Computer Systems Concepts: Data, Memory, Compilation, and the Stack

**Domain:** `systems`
**Level:** Beginner-friendly intro, intermediate/advanced rigor
**Prerequisites:** basic programming (any language), comfort with a terminal;
no prior computer-architecture or compilers background needed

## Summary

A machine-level survey of how programs actually run, once you get below
the language you wrote them in. Covers four pillars, each grounded in real
measurements taken on this machine rather than textbook diagrams alone:
**data representation** (two's complement integers and their overflow,
IEEE-754 floats and why `0.1 + 0.2 != 0.3`, derived down to the bit
level), the **memory hierarchy and caching** (a real ~5x row-major vs.
column-major NumPy benchmark, and a stride benchmark that isolates the
64-byte cache line), the **compilation pipeline** (preprocessing,
compilation, assembly, and linking, run for real with `gcc -E`/`-S`/`-c`
on a small C program, inspecting the actual intermediate artifacts), and
the **stack & calling conventions** (a real disassembled stack frame
showing the Windows x64 calling convention's register- and stack-passed
arguments, plus a measured, real per-call stack frame size from a
recursive C program). This is deliberately the *machine-facing* layer —
bits, cache lines, object files, stack frames — distinct from a
companion tutorial on OS-level abstractions (processes, virtual memory,
scheduling) that sits one layer up.

## Learning objectives

- Explain two's complement's wraparound behavior and derive its value
  formula and representable range; decompose any `float64` into its real
  sign/exponent/mantissa bits and explain precisely why `0.1 + 0.2 !=
  0.3` at the bit level.
- Explain spatial and temporal locality and cache lines, and predict
  (then measure) why one memory access pattern over the *same data* can
  be several times slower than another.
- Walk a C program through all four stages of compilation — preprocessing,
  compilation to assembly, assembling to an object file, and linking —
  and read the real intermediate artifacts (macro-expanded source,
  assembly, a symbol table) at each stage.
- Explain what a stack frame contains and how a calling convention
  determines where arguments and locals live; read a real disassembled
  function's prologue/epilogue and argument-passing, and measure a real
  program's per-call stack growth.
- Know where each of these four concepts shows up in real systems (Ariane
  5's overflow bug, columnar databases, build systems, stack-overflow
  exploits) and where the simplified models here break down in practice
  (UB-driven compiler optimizations, hardware-specific calling
  conventions, optimized-build assembly looking nothing like `-O0`
  assembly).

## Contents

- `tutorial.ipynb` — theory, visuals, and implementation
- `src/` — real C source compiled and run from the notebook:
  `pipeline_demo.c` (compilation pipeline), `calling_convention.c`
  (stack frame / calling convention), `stack_growth.c` (recursive stack
  growth measurement)

## References

- Bryant, R. E. & O'Hallaron, D. R., *Computer Systems: A Programmer's
  Perspective* (3rd ed.), Pearson.
- IEEE Std 754-2019, *IEEE Standard for Floating-Point Arithmetic*.
- Goldberg, D. (1991), *What Every Computer Scientist Should Know About
  Floating-Point Arithmetic*, ACM Computing Surveys.
- Drepper, U. (2007), *What Every Programmer Should Know About Memory*,
  Red Hat.
- Dean, J. (attrib.); interactive visualization by Colin Scott, "Latency
  Numbers Every Programmer Should Know."
- Microsoft, "x64 calling convention," MSVC/Windows documentation.
- Matz, M. et al., *System V Application Binary Interface, AMD64
  Architecture Processor Supplement*.
- Gustafson, J. L. & Yonemoto, I. (2017), *Beating Floating Point at its
  Own Game: Posit Arithmetic*.
- Levine, J. R., *Linkers and Loaders*, Morgan Kaufmann.
