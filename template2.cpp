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
#define vi vector<int>
#define vll vector<ll>

// **Constants**
const int MOD = 1e9 + 7;
const int INF = INT_MAX;
const double PI = acos(-1);

// **Sorting Algorithms**
void bubbleSort(vi &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void quickSort(vi &arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high], i = low - 1;
        for (int j = low; j < high; j++)
            if (arr[j] <= pivot)
                swap(arr[++i], arr[j]);
        swap(arr[i + 1], arr[high]);
        quickSort(arr, low, i);
        quickSort(arr, i + 2, high);
    }
}

void mergeSort(vi &arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    vector<int> temp;
    int i = l, j = m + 1;
    while (i <= m && j <= r)
        temp.push_back(arr[i] < arr[j] ? arr[i++] : arr[j++]);
    while (i <= m) temp.push_back(arr[i++]);
    while (j <= r) temp.push_back(arr[j++]);
    for (int k = l; k <= r; k++) arr[k] = temp[k - l];
}

// **Graph Algorithms**
struct DSU {
    vi parent, rank;
    DSU(int n) : parent(n), rank(n, 1) { iota(all(parent), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa != pb) {
            if (rank[pa] > rank[pb]) parent[pb] = pa;
            else if (rank[pa] < rank[pb]) parent[pa] = pb;
            else { parent[pb] = pa; rank[pa]++; }
        }
    }
};

// **Binary Exponentiation**
ll binPow(ll base, ll exp, ll mod = MOD) {
    ll res = 1;
    while (exp) {
        if (exp % 2) res = res * base % mod;
        base = base * base % mod;
        exp /= 2;
    }
    return res;
}

// **Greatest Common Divisor (GCD)**
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

// **Segment Tree**
struct SegmentTree {
    vi tree, arr;
    int n;
    SegmentTree(vi &input) {
        arr = input;
        n = input.size();
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }
    void build(int node, int start, int end) {
        if (start == end) tree[node] = arr[start];
        else {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }
    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return INF;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return min(query(2 * node + 1, start, mid, l, r), query(2 * node + 2, mid + 1, end, l, r));
    }
};

// **Trie Data Structure**
struct TrieNode {
    TrieNode *children[26];
    bool isEnd;
    TrieNode() { fill(begin(children), end(children), nullptr); isEnd = false; }
};
struct Trie {
    TrieNode *root;
    Trie() { root = new TrieNode(); }
    void insert(string word) {
        TrieNode *node = root;
        for (char c : word) {
            if (!node->children[c - 'a']) node->children[c - 'a'] = new TrieNode();
            node = node->children[c - 'a'];
        }
        node->isEnd = true;
    }
    bool search(string word) {
        TrieNode *node = root;
        for (char c : word) {
            if (!node->children[c - 'a']) return false;
            node = node->children[c - 'a'];
        }
        return node->isEnd;
    }
};

// **Bit Manipulation**
bool isPowerOfTwo(int n) { return (n > 0) && (n & (n - 1)) == 0; }

// **Dijkstra's Algorithm**
vector<int> dijkstra(vector<vector<pii>> &graph, int src) {
    int n = graph.size();
    vector<int> dist(n, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first, node = pq.top().second;
        pq.pop();
        if (d > dist[node]) continue;
        for (auto [adj, w] : graph[node]) {
            if (dist[node] + w < dist[adj]) {
                dist[adj] = dist[node] + w;
                pq.push({dist[adj], adj});
            }
        }
    }
    return dist;
}

// **N-Queens Backtracking**
void solveNQueens(int n, int row, vector<string> &board, vector<vector<string>> &res, vi &cols, vi &diag1, vi &diag2) {
    if (row == n) { res.push_back(board); return; }
    for (int col = 0; col < n; col++) {
        if (!cols[col] && !diag1[row + col] && !diag2[row - col + n - 1]) {
            board[row][col] = 'Q';
            cols[col] = diag1[row + col] = diag2[row - col + n - 1] = 1;
            solveNQueens(n, row + 1, board, res, cols, diag1, diag2);
            board[row][col] = '.';
            cols[col] = diag1[row + col] = diag2[row - col + n - 1] = 0;
        }
    }
}

// **Main Function**
int main() {
    FAST_IO;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vi arr(n);
        for (int &x : arr) cin >> x;
        quickSort(arr, 0, n - 1);
        for (int x : arr) cout << x << " ";
        cout << "\n";
    }
    return 0;
}
