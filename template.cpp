#include <bits/stdc++.h>
using namespace std;

// **Fast Input/Output**
#define FAST_IO ios::sync_with_stdio(false); cin.tie(nullptr);
#define ll long long
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pii pair<int, int>

// **Constants**
const int MOD = 1e9 + 7;
const int INF = INT_MAX;

// **Graph Representation**
vector<int> adj[100005], revAdj[100005];
bool visited[100005];

// **DFS for Graph Traversal**
void dfs(int node) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) dfs(neighbor);
    }
}

// **BFS for Shortest Path (Unweighted Graph)**
vector<int> bfs(int start, int n) {
    vector<int> dist(n, INF);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int node = q.front(); q.pop();
        for (int neighbor : adj[node]) {
            if (dist[neighbor] == INF) {
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
            }
        }
    }
    return dist;
}

// **Dijkstra’s Algorithm (Shortest Path)**
vector<int> dijkstra(int n, int src, vector<vector<pii>> &graph) {
    vector<int> dist(n, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second; pq.pop();
        if (d > dist[u]) continue;
        for (auto &[v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// **Bellman-Ford Algorithm (Handles Negative Weights)**
vector<int> bellmanFord(int V, int src, vector<vector<int>>& edges) {
    vector<int> dist(V, INF);
    dist[src] = 0;
    for (int i = 0; i < V - 1; i++) {
        for (auto e : edges) {
            if (dist[e[0]] != INF && dist[e[0]] + e[2] < dist[e[1]])
                dist[e[1]] = dist[e[0]] + e[2];
        }
    }
    return dist;
}

// **Floyd-Warshall Algorithm (All Pairs Shortest Path)**
void floydWarshall(vector<vector<int>>& graph, int V) {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}

// **Topological Sorting (Kahn's Algorithm - BFS)**
vector<int> topological_sort(int n) {
    vector<int> in_degree(n, 0);
    for (int i = 0; i < n; i++)
        for (int v : adj[i]) in_degree[v]++;
    
    queue<int> q;
    for (int i = 0; i < n; i++) if (in_degree[i] == 0) q.push(i);

    vector<int> topo_order;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        topo_order.push_back(node);
        for (int neighbor : adj[node]) {
            if (--in_degree[neighbor] == 0) q.push(neighbor);
        }
    }
    return topo_order;
}

// **Tarjan's Algorithm for Strongly Connected Components (SCC)**
vector<int> disc, low, scc;
stack<int> st;
int timer, scc_count;
void tarjanDFS(int u) {
    disc[u] = low[u] = ++timer;
    st.push(u);
    for (int v : adj[u]) {
        if (disc[v] == -1) {
            tarjanDFS(v);
            low[u] = min(low[u], low[v]);
        } else if (scc[v] == -1) {
            low[u] = min(low[u], disc[v]);
        }
    }
    if (low[u] == disc[u]) {
        while (true) {
            int v = st.top(); st.pop();
            scc[v] = scc_count;
            if (u == v) break;
        }
        scc_count++;
    }
}

// **Dynamic Programming (DP) Algorithms**

// **0/1 Knapsack Problem**
int knapsack(vector<int>& weight, vector<int>& value, int W, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weight[i - 1] <= w)
                dp[i][w] = max(value[i - 1] + dp[i - 1][w - weight[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][W];
}

// **Longest Common Subsequence (LCS)**
int LCS(string a, string b) {
    int n = a.length(), m = b.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

// **Longest Increasing Subsequence (LIS - DP + Binary Search)**
int LIS(vector<int>& arr) {
    vector<int> sub;
    for (int x : arr) {
        auto it = lower_bound(sub.begin(), sub.end(), x);
        if (it == sub.end()) sub.push_back(x);
        else *it = x;
    }
    return sub.size();
}

// **Subset Sum Problem**
bool subsetSum(vector<int>& arr, int sum) {
    int n = arr.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
    for (int i = 0; i <= n; i++) dp[i][0] = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= arr[i - 1]) dp[i][j] = dp[i][j] || dp[i - 1][j - arr[i - 1]];
        }
    }
    return dp[n][sum];
}

// **Main Function**
int main() {
    FAST_IO;
    int t;
    cin >> t;
    while (t--) {
        // Your solution goes here
    }
    return 0;
}
