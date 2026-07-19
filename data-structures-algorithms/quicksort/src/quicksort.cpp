// Quicksort (Lomuto partition scheme, randomized pivot) with instrumentation.
// Reads N integers from stdin (space-separated), sorts them, and prints:
//   - the sorted array
//   - the number of comparisons performed
//   - the number of swaps performed
//   - the wall-clock time in microseconds
//
// Build:  g++ -O2 -std=c++17 quicksort.cpp -o quicksort
// Run:    echo "5 3 8 1 9 2" | ./quicksort

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

static long long comparisons = 0;
static long long swaps = 0;

void doSwap(std::vector<long long>& a, int i, int j) {
    if (i == j) return;
    std::swap(a[i], a[j]);
    swaps++;
}

// Lomuto partition: everything <= pivot ends up left of the returned index.
int partition(std::vector<long long>& a, int lo, int hi, std::mt19937& rng) {
    // Randomized pivot selection avoids the O(n^2) worst case on
    // already-sorted or adversarial input -- this is the standard fix.
    std::uniform_int_distribution<int> dist(lo, hi);
    int pivotIndex = dist(rng);
    doSwap(a, pivotIndex, hi);
    long long pivot = a[hi];

    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        comparisons++;
        if (a[j] <= pivot) {
            i++;
            doSwap(a, i, j);
        }
    }
    doSwap(a, i + 1, hi);
    return i + 1;
}

void quicksort(std::vector<long long>& a, int lo, int hi, std::mt19937& rng) {
    if (lo >= hi) return;
    int p = partition(a, lo, hi, rng);
    quicksort(a, lo, p - 1, rng);
    quicksort(a, p + 1, hi, rng);
}

int main() {
    std::vector<long long> a;
    long long x;
    while (std::cin >> x) a.push_back(x);
    if (a.empty()) {
        std::cerr << "no input\n";
        return 1;
    }

    std::mt19937 rng(12345); // fixed seed for reproducible instrumentation counts

    auto start = std::chrono::high_resolution_clock::now();
    quicksort(a, 0, static_cast<int>(a.size()) - 1, rng);
    auto end = std::chrono::high_resolution_clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "sorted: ";
    for (size_t k = 0; k < a.size(); k++) {
        std::cout << a[k] << (k + 1 < a.size() ? " " : "\n");
    }
    std::cout << "n=" << a.size() << "\n";
    std::cout << "comparisons=" << comparisons << "\n";
    std::cout << "swaps=" << swaps << "\n";
    std::cout << "microseconds=" << micros << "\n";
    return 0;
}
