#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const long long MOD = 1000000007;

int n;
int a[505][505];
long long dp[505][505];

// dp[i][j] = number of non-crossing spanning trees for nodes i to j (inclusive)
// These nodes are on an arc

long long solve(int l, int r) {
    if (l > r) return 1;  // empty interval
    if (l == r) return 1;  // single node, no edges
    
    if (dp[l][r] != -1) return dp[l][r];
    
    long long ans = 0;
    
    // Pick an edge from l to some node k in [l+1, r]
    for (int k = l + 1; k <= r; k++) {
        if (a[l][k] == 1) {
            // Edge (l, k) exists
            // Nodes [l+1, k-1] are between l and k (form a tree)
            // Nodes [k, r] include k and everything after (form a tree)
            long long left = solve(l + 1, k - 1);
            long long right = solve(k, r);
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
    
    // For a circle, break at node 0 and connect to node k
    long long answer = 0;
    
    for (int k = 1; k < n; k++) {
        if (a[0][k] == 1) {
            long long left = solve(1, k - 1);
            long long right = solve(k, n - 1);
            answer = (answer + left * right % MOD) % MOD;
        }
    }
    
    cout << answer << endl;
    
    return 0;
}
