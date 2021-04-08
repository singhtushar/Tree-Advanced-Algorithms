/*
 Author: singhtushar
 SPOJ: https://www.spoj.com/problems/LCASQ/
*/

#include <bits/stdc++.h>
#define  FAST   ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define  el     "\n"
#define  all(v) v.begin(),v.end()
#define  pb     push_back
#define  pf     push_front
#define  ff     first
#define  ss     second
#define  vi     vector<int>
#define  vii    vector<pair<int,int>>
#define  pii    pair<int,int>
#define  int    long long
using namespace std;
const int mod = 1e9 + 7;
void IOS() {
	FAST;
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}
const int MAX_N = 10005;
vector<int> adj[MAX_N];
int parent[MAX_N];
int depth[MAX_N];
vector<vector<int>> up;
int LOG;

void dfs(int node, int par = 0, int height = 0) {
	parent[node] = par;
	depth[node] = height;
	for (auto it : adj[node]) {
		if (it != par)
			dfs(it, node, height + 1);
	}
}

void binary_lifting(int n) {
	LOG = ceil(log2(n));
	up = vector<vector<int>>(n, vector<int>(LOG));
	for (int v = 0; v < n; v++)
		up[v][0] = parent[v];

	for (int j = 1; j < LOG; j++) {
		for (int v = 0; v < n; v++) {
			up[v][j] = up[up[v][j - 1]][j - 1];
		}
	}
}

int lca(int a, int b) {
	if (depth[a] < depth[b])
		swap(a, b);
	int k = depth[a] - depth[b];
	for (int j = LOG - 1; j >= 0; j--) {
		if (k & (1 << j))
			a = up[a][j];
	}
	if (a == b)
		return a;
	for (int i = LOG - 1; i >= 0; i--) {
		if (up[a][i] != up[b][i]) {
			a = up[a][i];
			b = up[b][i];
		}
	}
	return up[a][0];
}

signed main() {
	IOS();
	int t = 1;
	// cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			int m;
			cin >> m;
			for (int j = 0; j < m; j++) {
				int u;
				cin >> u;
				adj[i].pb(u);
			}
		}
		dfs(0);
		binary_lifting(n);
		int q;
		cin >> q;
		while (q--) {
			int u, v;
			cin >> u >> v;
			cout << lca(u, v) << el;
		}
	}
	return 0;
}