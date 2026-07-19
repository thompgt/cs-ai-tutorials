// Binary search, plus the lower_bound / upper_bound variants, with
// instrumentation (comparison counts + wall-clock timing).
//
// Input format (stdin, whitespace-separated):
//   <target> <n> <a_0> <a_1> ... <a_{n-1}>
// where a_0..a_{n-1} is already sorted ascending.
//
// Output (stdout, one "key=value" per line):
//   found=<index of an element == target, or -1>
//   lower_bound=<first index i with a[i] >= target, or n>
//   upper_bound=<first index i with a[i] >  target, or n>
//   comparisons_found=<comparisons used by the equality search>
//   comparisons_lower=<comparisons used by lower_bound>
//   comparisons_upper=<comparisons used by upper_bound>
//   comparisons=<sum of the three, for convenience>
//   microseconds=<wall-clock time for all three searches combined>
//
// Build:  g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ \
//           binary_search.cpp -o binary_search.exe
// Run:    echo "7 6 1 3 5 7 7 9" | ./binary_search.exe

#include <iostream>
#include <vector>
#include <chrono>

// Classic equality search: does `target` occur in a[lo..hi)? Returns an
// index where a[i] == target, or -1 if absent.
//
// Loop invariant: if `target` is present anywhere in a, it is present
// within a[lo..hi) at the top of every iteration. Initially that's true
// because [lo, hi) = [0, n) covers the whole array. Each iteration either
// finds the target, or shrinks [lo, hi) to a strictly smaller half that
// still satisfies the invariant (proved in the notebook).
long long findEquality(const std::vector<long long>& a, long long target, long long& comparisons) {
    long long lo = 0, hi = static_cast<long long>(a.size()); // [lo, hi)
    while (lo < hi) {
        // THE CLASSIC BUG: `mid = (lo + hi) / 2` can overflow when lo and hi
        // are both large (their sum exceeds the integer type's range) even
        // though neither individually is out of range or close to it. This
        // bit real production code -- see Bentley's Programming Pearls and
        // the notebook's "Limitations & debates" section. The fix below
        // never sums lo and hi, so it cannot overflow.
        long long mid = lo + (hi - lo) / 2;
        comparisons++; // one "comparison" per iteration, for a fair apples-to-apples
                        // count against lower_bound/upper_bound below
        if (a[mid] == target) {
            return mid;
        } else if (a[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return -1;
}

// lower_bound: first index i in [0, n] with a[i] >= target (n if none).
//
// Invariant: everything in a[0..lo) is known to be < target, and
// everything in a[hi..n) is known to be >= target. [lo, hi) is the
// undetermined region. Note this invariant is subtly different from the
// equality search's: there is no early return on a match, because we're
// not looking for *a* match, we're looking for the *first* index that
// could hold one.
long long lowerBound(const std::vector<long long>& a, long long target, long long& comparisons) {
    long long lo = 0, hi = static_cast<long long>(a.size());
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        comparisons++;
        if (a[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

// upper_bound: first index i in [0, n] with a[i] > target (n if none).
//
// Same invariant shape as lower_bound, but the comparison flips from
// `< target` to `<= target` -- that one-character difference is the
// entire distinction between "first element not less than target" and
// "first element greater than target".
long long upperBound(const std::vector<long long>& a, long long target, long long& comparisons) {
    long long lo = 0, hi = static_cast<long long>(a.size());
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        comparisons++;
        if (a[mid] <= target) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

int main() {
    long long target, n;
    if (!(std::cin >> target >> n)) {
        std::cerr << "expected: <target> <n> <a_0> ... <a_{n-1}>\n";
        return 1;
    }
    std::vector<long long> a(n);
    for (long long i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    long long cmpFound = 0, cmpLower = 0, cmpUpper = 0;

    auto start = std::chrono::high_resolution_clock::now();
    long long found = findEquality(a, target, cmpFound);
    long long lb = lowerBound(a, target, cmpLower);
    long long ub = upperBound(a, target, cmpUpper);
    auto end = std::chrono::high_resolution_clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "found=" << found << "\n";
    std::cout << "lower_bound=" << lb << "\n";
    std::cout << "upper_bound=" << ub << "\n";
    std::cout << "comparisons_found=" << cmpFound << "\n";
    std::cout << "comparisons_lower=" << cmpLower << "\n";
    std::cout << "comparisons_upper=" << cmpUpper << "\n";
    std::cout << "comparisons=" << (cmpFound + cmpLower + cmpUpper) << "\n";
    std::cout << "microseconds=" << micros << "\n";
    return 0;
}
