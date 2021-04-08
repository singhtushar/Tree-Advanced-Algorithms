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

vector<int> adj[10000];
int up[10000][14];
int LOG = 14;
int parent[10000];
int depth[10000];

void dfs(int node, int par = 0, int level = 0) {
	parent[node] = par;
	depth[node] = level;
	for (auto it : adj[node]) {
		if (it != par)
			dfs(it, node, level + 1);
	}
}

void binary_lifting(int n) {
	LOG = log2(n) + 1;
	parent[0] = 0;
	for (int v = 0; v < n; v++) {
		up[v][0] = parent[v];
	}
	for (int i = 1; i < LOG; i++) {
		for (int v = 0; v < n; v++) {
			up[v][i] = up[up[v][i - 1]][i - 1];
		}
	}
}

int lca(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);
	int d = depth[u] - depth[v];
	for (int i = LOG - 1; i >= 0; i--) {
		if (d & (1ll << i))
			u = up[u][i];
	}
	if (u == v)
		return u;
	for (int i = LOG - 1; i >= 0; i--) {
		if (up[u][i] != up[v][i]) {
			u = up[u][i];
			v = up[v][i];
		}
	}
	return up[u][0];
}

signed main() {
	IOS();
	int t = 1;
	int tc = 1;
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