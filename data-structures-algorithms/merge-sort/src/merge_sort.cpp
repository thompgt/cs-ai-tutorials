// Merge sort (top-down, recursive) with instrumentation.
// Reads N integers from stdin (space-separated), sorts them, and prints:
//   - the sorted array
//   - the number of comparisons performed during merges
//   - the number of element moves/copies performed
//   - the wall-clock time in microseconds
//
// Merge sort needs O(n) auxiliary space: each merge step copies both
// input subarrays into a scratch buffer before writing the merged result
// back into the original range. Unlike quicksort's in-place partitioning,
// this scratch buffer is unavoidable for the standard top-down/bottom-up
// merge sort -- that O(n) extra space is the real cost paid for the
// guaranteed Theta(n log n) worst case and stability (see tutorial.ipynb).
//
// Build:  g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ merge_sort.cpp -o merge_sort
// Run:    echo "5 3 8 1 9 2" | ./merge_sort

#include <iostream>
#include <vector>
#include <chrono>

static long long comparisons = 0;
static long long moves = 0;

// Merge two already-sorted runs a[lo..mid] and a[mid+1..hi] into one sorted
// run a[lo..hi], using `buf` as O(n) scratch space (only the [lo, hi] slice
// of it is touched here).
void merge(std::vector<long long>& a, std::vector<long long>& buf, int lo, int mid, int hi) {
    int i = lo;      // cursor into left run [lo, mid]
    int j = mid + 1; // cursor into right run [mid+1, hi]
    int k = lo;      // write cursor into buf

    // Two-pointer merge: at every step, whichever run's front element is
    // smaller (or equal -- see stability note in tutorial.ipynb) gets
    // copied out first. Using "<=" for the left run's element is what
    // makes this merge stable: a tie always takes the left (earlier-input)
    // element first, so equal keys never cross each other.
    while (i <= mid && j <= hi) {
        comparisons++;
        if (a[i] <= a[j]) {
            buf[k++] = a[i++];
        } else {
            buf[k++] = a[j++];
        }
        moves++;
    }
    // Drain whichever run still has leftover elements (no comparisons
    // needed -- everything remaining is already known to be >= what's
    // been written so far).
    while (i <= mid) {
        buf[k++] = a[i++];
        moves++;
    }
    while (j <= hi) {
        buf[k++] = a[j++];
        moves++;
    }
    // Copy the merged run back from scratch space into the real array.
    for (int p = lo; p <= hi; p++) {
        a[p] = buf[p];
        moves++;
    }
}

void mergeSort(std::vector<long long>& a, std::vector<long long>& buf, int lo, int hi) {
    if (lo >= hi) return; // 0 or 1 elements: already sorted, base case
    int mid = lo + (hi - lo) / 2;
    mergeSort(a, buf, lo, mid);
    mergeSort(a, buf, mid + 1, hi);
    merge(a, buf, lo, mid, hi);
}

int main() {
    std::vector<long long> a;
    long long x;
    while (std::cin >> x) a.push_back(x);
    if (a.empty()) {
        std::cerr << "no input\n";
        return 1;
    }

    // Single scratch buffer allocated once and reused across all merge
    // calls -- this is the algorithm's O(n) auxiliary space, allocated up
    // front rather than per-call.
    std::vector<long long> buf(a.size());

    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(a, buf, 0, static_cast<int>(a.size()) - 1);
    auto end = std::chrono::high_resolution_clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "sorted: ";
    for (size_t k = 0; k < a.size(); k++) {
        std::cout << a[k] << (k + 1 < a.size() ? " " : "\n");
    }
    std::cout << "n=" << a.size() << "\n";
    std::cout << "comparisons=" << comparisons << "\n";
    std::cout << "moves=" << moves << "\n";
    std::cout << "microseconds=" << micros << "\n";
    return 0;
}
