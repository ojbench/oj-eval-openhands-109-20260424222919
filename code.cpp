#include <iostream>
#include <cstring>
using namespace std;

const long long MOD = 1000000007;

int n;
int a[505][505];
long long dp[505][505];

// dp[i][j] = number of non-crossing trees for nodes i, i+1, ..., j (consecutive on arc)
// Standard formula for non-crossing trees on an arc

long long solve(int l, int r) {
    if (l > r) return 1;
    if (l == r) return 1;
    
    if (dp[l][r] != -1) return dp[l][r];
    
    long long ans = 0;
    
    // Pick a root r in [l, r]
    // All other nodes must connect to this root
    // For non-crossing property, we partition the nodes
    
    for (int root = l; root <= r; root++) {
        // Root is at position 'root'
        // Nodes [l, root-1] and [root+1, r] form subtrees of root
        
        long long ways = 1;
        
        // Count ways to form subtrees on the left
        long long left_ways = 1;
        for (int i = l; i < root; i++) {
            if (a[i][root] == 1) {
                // Node i can connect to root
                // We need to count this...
            }
        }
        
        // This is getting complicated too
    }
    
    // Let me try the standard Catalan-based formula
    // For nodes on an arc [l, r], we use:
    for (int k = l; k <= r; k++) {
        // Pick node k as a "separator"
        // Nodes [l, k-1] and [k+1, r] form independent subtrees
        long long left = solve(l, k - 1);
        long long right = solve(k + 1, r);
        
        // But we need to ensure k is connected...
        // If l < k, we need edge (l-1, k) or similar
        // This doesn't work for arcs
    }
    
    // Actually, the standard formula is:
    // dp[l][r] = sum over k in [l+1, r] of: (edge l to k exists) * dp[l+1][k-1] * dp[k+1][r]
    for (int k = l + 1; k <= r; k++) {
        if (a[l][k] == 1) {
            long long left = solve(l + 1, k - 1);
            long long right = solve(k + 1, r);
            ans = (ans + left * right % MOD) % MOD;
        }
    }
    
    dp[l][r] = ans;
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
    
    // Try computing the answer directly as solve(0, n-1)
    // treating the circle as if node 0 and node n-1 are adjacent
    
    long long answer = 0;
    
    // Standard approach: break circle at node 0
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
