// Longest Common Subsequence (LCS) via dynamic programming, with full
// backtracking reconstruction and a diff-style rendering mode.
//
// Reads two strings from stdin, one per line. Prints:
//   - the LCS length
//   - the reconstructed LCS string
//   - a diff-style view of both inputs against the LCS
//   - the wall-clock time in microseconds spent building the DP table
//
// Build:  g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ lcs.cpp -o lcs
// Run:    printf "ABCBDAB\nBDCABA\n" | ./lcs

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

// dp[i][j] = length of the LCS of X[0..i) and Y[0..j)
// Recurrence: if X[i-1] == Y[j-1], dp[i][j] = dp[i-1][j-1] + 1
//             else                 dp[i][j] = max(dp[i-1][j], dp[i][j-1])
std::vector<std::vector<int>> buildTable(const std::string& X, const std::string& Y) {
    int m = static_cast<int>(X.size());
    int n = static_cast<int>(Y.size());
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else if (dp[i - 1][j] >= dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = dp[i][j - 1];
            }
        }
    }
    return dp;
}

// Walk from dp[m][n] back to dp[0][0], following whichever choice produced
// each cell, to recover the actual LCS string (not just its length).
// On ties between "came from above" and "came from the left" this always
// prefers "above" (matches the >= in buildTable) -- one of possibly many
// valid maximum-length subsequences.
std::string reconstruct(const std::vector<std::vector<int>>& dp, const std::string& X, const std::string& Y) {
    int i = static_cast<int>(X.size());
    int j = static_cast<int>(Y.size());
    std::string lcs;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs.push_back(X[i - 1]);
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    std::reverse(lcs.begin(), lcs.end());
    return lcs;
}

// Diff-style rendering: walk the same backtrace, but instead of only
// collecting matched characters, label every character of X and Y as
// "kept" (part of the LCS) or "removed"/"added". This is the same
// traversal reconstruct() does, just recording both sides instead of
// discarding the non-matching characters.
struct DiffLines {
    std::string xLine; // X with removed characters marked
    std::string yLine; // Y with added characters marked
};

DiffLines buildDiff(const std::vector<std::vector<int>>& dp, const std::string& X, const std::string& Y) {
    int i = static_cast<int>(X.size());
    int j = static_cast<int>(Y.size());
    std::string xMarks, yMarks; // built back-to-front, reversed at the end

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            xMarks.push_back('='); // kept
            yMarks.push_back('=');
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            xMarks.push_back('-'); // removed from X
            i--;
        } else {
            yMarks.push_back('+'); // added in Y
            j--;
        }
    }
    while (i > 0) { xMarks.push_back('-'); i--; }
    while (j > 0) { yMarks.push_back('+'); j--; }

    std::reverse(xMarks.begin(), xMarks.end());
    std::reverse(yMarks.begin(), yMarks.end());

    DiffLines out;
    // Build the "- removed" line for X and "+ added" line for Y, git-diff style.
    int xi = 0;
    for (char m : xMarks) {
        if (m == '-') { out.xLine += "-"; out.xLine += X[xi]; out.xLine += " "; }
        else { out.xLine += " "; out.xLine += X[xi]; out.xLine += " "; }
        xi++;
    }
    int yi = 0;
    for (char m : yMarks) {
        if (m == '+') { out.yLine += "+"; out.yLine += Y[yi]; out.yLine += " "; }
        else { out.yLine += " "; out.yLine += Y[yi]; out.yLine += " "; }
        yi++;
    }
    return out;
}

int main() {
    std::string X, Y;
    if (!std::getline(std::cin, X)) { std::cerr << "expected two lines of input\n"; return 1; }
    if (!std::getline(std::cin, Y)) { std::cerr << "expected two lines of input\n"; return 1; }

    auto start = std::chrono::high_resolution_clock::now();
    auto dp = buildTable(X, Y);
    auto end = std::chrono::high_resolution_clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::string lcs = reconstruct(dp, X, Y);
    DiffLines diff = buildDiff(dp, X, Y);

    int m = static_cast<int>(X.size());
    int n = static_cast<int>(Y.size());

    std::cout << "m=" << m << "\n";
    std::cout << "n=" << n << "\n";
    std::cout << "lcs_length=" << dp[m][n] << "\n";
    std::cout << "lcs=" << lcs << "\n";
    std::cout << "diff_x=" << diff.xLine << "\n";
    std::cout << "diff_y=" << diff.yLine << "\n";
    std::cout << "microseconds=" << micros << "\n";
    return 0;
}
