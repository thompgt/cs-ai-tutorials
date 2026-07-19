// 0/1 Knapsack -- three real, instrumented implementations:
//   1) Full 2D DP table (dp[i][w]), used for correctness, backtracking the
//      chosen items, and visualizing the whole table as a heatmap.
//   2) Space-optimized 1D rolling-array DP (O(n) space, O(n*W) time), used
//      for the performance benchmark against n and W.
//   3) Brute-force 2^n subset enumeration (small n only), used as an
//      independent correctness cross-check against the DP.
//
// All three are timed with std::chrono and print their own wall-clock time.
//
// stdin format:
//   line 1: n capacity
//   line 2: n whitespace-separated weights
//   line 3: n whitespace-separated values
//
// argv[1] selects which method(s) to run: "2d", "1d", "brute", or "all"
// (default "all" runs 2d + 1d, and brute only if n <= 24 to stay fast).
//
// Build:  g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ knapsack.cpp -o knapsack.exe
// Run:    echo "4 7
// 1 3 4 5
// 1 4 5 7" | ./knapsack.exe all

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

using Clock = std::chrono::high_resolution_clock;

struct Items {
    int n;
    int capacity;
    std::vector<long long> weight;
    std::vector<long long> value;
};

Items readItems() {
    Items it;
    std::cin >> it.n >> it.capacity;
    it.weight.resize(it.n);
    it.value.resize(it.n);
    for (int i = 0; i < it.n; i++) std::cin >> it.weight[i];
    for (int i = 0; i < it.n; i++) std::cin >> it.value[i];
    return it;
}

void printItemList(const std::string& label, const std::vector<int>& chosen) {
    std::cout << label << ":";
    for (int idx : chosen) std::cout << " " << idx;
    std::cout << "\n";
}

// ---------------------------------------------------------------------
// 1) Full 2D DP table.
//
// Recurrence:
//   dp[i][w] = dp[i-1][w]                                  if weight[i-1] > w
//            = max(dp[i-1][w], dp[i-1][w-weight[i-1]] + value[i-1])  otherwise
//
// dp[i][w] = best achievable value using only the first i items with
// capacity w. dp[0][w] = 0 for all w (no items -> no value).
// ---------------------------------------------------------------------
void run2D(const Items& it, bool printTable) {
    auto start = Clock::now();
    int n = it.n, W = it.capacity;
    std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        long long w_i = it.weight[i - 1];
        long long v_i = it.value[i - 1];
        for (int w = 0; w <= W; w++) {
            if (w_i > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - w_i] + v_i);
            }
        }
    }

    // Backtrack from dp[n][W] to recover which items were taken, and the
    // (i, w) path of cells that actually contributed to the answer.
    std::vector<int> chosen;
    std::vector<std::pair<int, int>> path;
    int w = W;
    for (int i = n; i >= 1; i--) {
        path.push_back({i, w});
        if (dp[i][w] != dp[i - 1][w]) {
            chosen.push_back(i - 1); // 0-indexed item id
            w -= static_cast<int>(it.weight[i - 1]);
        }
    }
    path.push_back({0, w});
    std::reverse(chosen.begin(), chosen.end());
    std::reverse(path.begin(), path.end());

    auto end = Clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "2d_value=" << dp[n][W] << "\n";
    std::cout << "2d_time_us=" << micros << "\n";
    printItemList("2d_items", chosen);

    std::cout << "2d_path:";
    for (auto& p : path) std::cout << " " << p.first << "," << p.second;
    std::cout << "\n";

    if (printTable) {
        std::cout << "2d_table_rows=" << (n + 1) << " cols=" << (W + 1) << "\n";
        for (int i = 0; i <= n; i++) {
            std::cout << "table:";
            for (int wcol = 0; wcol <= W; wcol++) std::cout << " " << dp[i][wcol];
            std::cout << "\n";
        }
    }
}

// ---------------------------------------------------------------------
// 2) Space-optimized 1D rolling array.
//
// Collapse dp[i][*] into a single array dp[w], updated in place. Because
// dp[i][w] only ever depends on dp[i-1][w] and dp[i-1][w - weight_i] (both
// from the PREVIOUS item row), iterating w from HIGH to LOW during item i's
// update means every dp[w - weight_i] read still holds last item's value
// when we get to it. Iterating low-to-high would overwrite dp[w - weight_i]
// with THIS item's own contribution before we read it -- effectively
// allowing item i to be used twice in the same pass, which breaks the 0/1
// (take-it-once) constraint.
// ---------------------------------------------------------------------
long long run1D(const Items& it) {
    auto start = Clock::now();
    int n = it.n, W = it.capacity;
    std::vector<long long> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        long long w_i = it.weight[i];
        long long v_i = it.value[i];
        for (int w = W; w >= static_cast<int>(w_i); w--) {
            dp[w] = std::max(dp[w], dp[w - w_i] + v_i);
        }
    }

    auto end = Clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "1d_value=" << dp[W] << "\n";
    std::cout << "1d_time_us=" << micros << "\n";
    return dp[W];
}

// ---------------------------------------------------------------------
// 3) Brute force: enumerate all 2^n subsets, keep the best that fits.
// Only practical for small n (this repo caps it at n <= 24 by default).
// Used purely as an independent correctness cross-check against the DP.
// ---------------------------------------------------------------------
void runBrute(const Items& it) {
    auto start = Clock::now();
    int n = it.n, W = it.capacity;
    long long best = 0;
    long long bestMask = 0;
    long long limit = 1LL << n;

    for (long long mask = 0; mask < limit; mask++) {
        long long totalW = 0, totalV = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1LL << i)) {
                totalW += it.weight[i];
                totalV += it.value[i];
            }
        }
        if (totalW <= W && totalV > best) {
            best = totalV;
            bestMask = mask;
        }
    }

    auto end = Clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::vector<int> chosen;
    for (int i = 0; i < n; i++) {
        if (bestMask & (1LL << i)) chosen.push_back(i);
    }

    std::cout << "brute_value=" << best << "\n";
    std::cout << "brute_time_us=" << micros << "\n";
    printItemList("brute_items", chosen);
}

int main(int argc, char** argv) {
    std::string mode = "all";
    if (argc > 1) mode = argv[1];
    bool printTable = (argc > 2 && std::string(argv[2]) == "table");

    Items it = readItems();

    if (mode == "2d" || mode == "all") {
        run2D(it, printTable);
    }
    if (mode == "1d" || mode == "all") {
        run1D(it);
    }
    if (mode == "brute" || (mode == "all" && it.n <= 24)) {
        runBrute(it);
    }

    return 0;
}
