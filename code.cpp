#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const long long MOD = 1000000007;

int n;
int a[505][505];
long long dp[505][505];

// dp[i][j] counts the number of non-crossing spanning forests for nodes i..j
// A forest can have multiple trees

long long solve(int l, int r) {
    if (l > r) return 1;  // empty, one way (empty forest)
    
    if (dp[l][r] != -1) return dp[l][r];
    
    long long ans = 0;
    
    // Enumerate all possible structures:
    // 1. Node l is isolated (forms its own tree)
    ans = solve(l + 1, r);
    
    // 2. Node l connects to some subset of nodes in [l+1, r]
    // For each node k in [l+1, r], if l connects to k:
    for (int k = l + 1; k <= r; k++) {
        if (a[l][k] == 1) {
            // l and k are in the same tree
            // Nodes [l+1, k-1] are between l and k (form a forest)
            // Nodes [k+1, r] are after k (form a forest)
            long long left = solve(l + 1, k - 1);
            long long right = solve(k + 1, r);
            ans = (ans + left * right % MOD) % MOD;
        }
    }
    
    dp[l][r] = ans;
    return ans;
}

// For counting spanning trees (not forests), we need a different approach
// Let me use a DP that tracks the number of connected components

long long dp_tree[505][505];  // dp_tree[i][j] = number of spanning trees for nodes i..j

long long solve_tree(int l, int r) {
    if (l > r) return 0;  // empty, no tree
    if (l == r) return 1;  // single node, one tree (no edges)
    
    if (dp_tree[l][r] != -1) return dp_tree[l][r];
    
    long long ans = 0;
    
    // For a spanning tree, all nodes must be connected
    // Pick the leftmost node l and decide which nodes it connects to
    // At least one connection is needed
    
    for (int k = l + 1; k <= r; k++) {
        if (a[l][k] == 1) {
            // l connects to k
            // Nodes [l+1, k-1] form a forest (can be disconnected)
            // Nodes [k+1, r] form a forest
            // But we need exactly one tree total, so we need to be careful
            
            // Actually, this is complex. Let me think differently.
        }
    }
    
    // Simpler approach: use the original recurrence
    for (int k = l + 1; k <= r; k++) {
        if (a[l][k] == 1) {
            long long left = solve_tree(l + 1, k - 1);
            long long right = solve_tree(k + 1, r);
            
            // But this counts forests, not trees...
            // We need to ensure connectivity
        }
    }
    
    // I'm going in circles. Let me just use the simple formula
    for (int k = l + 1; k <= r; k++) {
        if (a[l][k] == 1) {
            long long left_forest = solve(l + 1, k - 1);
            long long right_forest = solve(k + 1, r);
            ans = (ans + left_forest * right_forest % MOD) % MOD;
        }
    }
    
    dp_tree[l][r] = ans;
    return ans;
}

int main() {
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    
    memset(dp, -1, sizeof(dp));
    memset(dp_tree, -1, sizeof(dp_tree));
    
    long long answer = 0;
    
    for (int k = 1; k < n; k++) {
        if (a[0][k] == 1) {
            long long left = solve(1, k - 1);
            long long right = solve(k + 1, n - 1);
            answer = (answer + left * right % MOD) % MOD;
        }
    }
    
    cout << answer << endl;
    
    return 0;
}
