// Knuth-Morris-Pratt (KMP) string matching, benchmarked against the naive
// sliding-window search, with instrumentation.
//
// Reads two lines from stdin:
//   line 1: the text to search in
//   line 2: the pattern to search for
//
// Prints:
//   naive_matches=<space-separated 0-indexed match positions>
//   naive_comparisons=<character comparisons performed by naive search>
//   naive_microseconds=<wall-clock time for naive search>
//   kmp_matches=<space-separated 0-indexed match positions>
//   kmp_failure_comparisons=<comparisons spent building the failure function>
//   kmp_search_comparisons=<comparisons spent during the linear search>
//   kmp_comparisons=<total KMP comparisons (failure + search)>
//   kmp_microseconds=<wall-clock time for KMP (failure function + search)>
//   match=<1 if naive_matches == kmp_matches, else 0>
//
// Build:  g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ kmp.cpp -o kmp
// Run:    printf "ABABABABCABABABABCABABABABC\nABABC\n" | ./kmp

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

// Naive search: try every starting offset in the text, compare character by
// character, and bail out on the first mismatch. Worst case O(n*m) -- e.g.
// text = "AAAA...AAA", pattern = "AAAA...AAB" forces (n-m+1)*m comparisons
// because every attempt matches almost the whole pattern before failing.
std::vector<int> naiveSearch(const std::string& text, const std::string& pattern, long long& comparisons) {
    std::vector<int> matches;
    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pattern.size());
    comparisons = 0;
    if (m == 0 || m > n) return matches;

    for (int start = 0; start + m <= n; start++) {
        int j = 0;
        while (j < m) {
            comparisons++;
            if (text[start + j] != pattern[j]) break;
            j++;
        }
        if (j == m) matches.push_back(start);
    }
    return matches;
}

// Build the failure function (a.k.a. prefix function / LPS array).
// fail[i] = length of the longest proper prefix of pattern[0..i] that is
// also a suffix of pattern[0..i]. Computed with a two-pointer scan that is
// itself amortized O(m): see the notebook's "Going deeper" section for the
// argument.
std::vector<int> buildFailureFunction(const std::string& pattern, long long& comparisons) {
    int m = static_cast<int>(pattern.size());
    std::vector<int> fail(m, 0);
    comparisons = 0;
    int k = 0; // length of the current matching prefix/suffix
    for (int i = 1; i < m; i++) {
        while (k > 0) {
            comparisons++;
            if (pattern[i] == pattern[k]) break;
            k = fail[k - 1];
        }
        if (k == 0) {
            // Either m == 1 (loop never entered) or the while loop above
            // exited via k hitting 0 without matching; either way we still
            // owe one comparison for pattern[i] vs pattern[k] (k == 0 case).
            comparisons++;
        }
        if (pattern[i] == pattern[k]) {
            k++;
        }
        fail[i] = k;
    }
    return fail;
}

// KMP search using a precomputed failure function. The text pointer i never
// moves backward -- every character of the text is examined a bounded
// number of times, giving O(n) for the search phase (O(n+m) overall with
// the failure-function build).
std::vector<int> kmpSearch(const std::string& text, const std::string& pattern,
                            const std::vector<int>& fail, long long& comparisons) {
    std::vector<int> matches;
    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pattern.size());
    comparisons = 0;
    if (m == 0 || m > n) return matches;

    int k = 0; // number of pattern characters currently matched
    for (int i = 0; i < n; i++) {
        while (k > 0) {
            comparisons++;
            if (text[i] == pattern[k]) break;
            k = fail[k - 1]; // skip using what we already know about the pattern
        }
        if (k == 0) {
            comparisons++;
        }
        if (text[i] == pattern[k]) {
            k++;
        }
        if (k == m) {
            matches.push_back(i - m + 1);
            k = fail[k - 1]; // continue looking for overlapping matches
        }
    }
    return matches;
}

int main() {
    std::string text, pattern;
    std::getline(std::cin, text);
    std::getline(std::cin, pattern);

    long long naiveComparisons = 0;
    auto naiveStart = std::chrono::high_resolution_clock::now();
    std::vector<int> naiveMatches = naiveSearch(text, pattern, naiveComparisons);
    auto naiveEnd = std::chrono::high_resolution_clock::now();
    auto naiveMicros = std::chrono::duration_cast<std::chrono::microseconds>(naiveEnd - naiveStart).count();

    long long failureComparisons = 0;
    long long searchComparisons = 0;
    auto kmpStart = std::chrono::high_resolution_clock::now();
    std::vector<int> fail = buildFailureFunction(pattern, failureComparisons);
    std::vector<int> kmpMatches = kmpSearch(text, pattern, fail, searchComparisons);
    auto kmpEnd = std::chrono::high_resolution_clock::now();
    auto kmpMicros = std::chrono::duration_cast<std::chrono::microseconds>(kmpEnd - kmpStart).count();

    std::cout << "naive_matches:";
    for (int p : naiveMatches) std::cout << " " << p;
    std::cout << "\n";
    std::cout << "naive_comparisons=" << naiveComparisons << "\n";
    std::cout << "naive_microseconds=" << naiveMicros << "\n";

    std::cout << "kmp_matches:";
    for (int p : kmpMatches) std::cout << " " << p;
    std::cout << "\n";
    std::cout << "kmp_failure_comparisons=" << failureComparisons << "\n";
    std::cout << "kmp_search_comparisons=" << searchComparisons << "\n";
    std::cout << "kmp_comparisons=" << (failureComparisons + searchComparisons) << "\n";
    std::cout << "kmp_microseconds=" << kmpMicros << "\n";

    std::cout << "match=" << (naiveMatches == kmpMatches ? 1 : 0) << "\n";

    return 0;
}
