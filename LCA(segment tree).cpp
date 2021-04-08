/*
 Author: @singhtushar
 SPOJ: https://www.spoj.com/problems/LCA/
 Time Complexity: O(m)-->preprocessing + O(q*log2m) --> Segment Tree
 Where m is euler path size
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

const int N = 1e3 + 5;
vector<int> adj[N];
vector<int> height(N);
vector<int> firstOcc(N);
vector<int> euler;
vector<int> seg;

void dfs(int node, int par = -1, int level = 0) {
	height[node] = level;
	firstOcc[node] = euler.size();
	euler.push_back(node);
	for (auto it : adj[node]) {
		if (it != par) {
			dfs(it, node, level + 1);
			euler.push_back(node);
		}
	}
}

void build(int ind, int low, int high) {
	if (low == high) {
		seg[ind] = euler[low];
		return;
	}
	int mid = (low + high) >> 1;
	build(2 * ind + 1, low, mid);
	build(2 * ind + 2, mid + 1, high);
	int left = seg[2 * ind + 1];
	int right = seg[2 * ind + 2];
	seg[ind] = (height[left] < height[right]) ? left : right;
}

int query(int ind, int low, int high, int l, int r) {
	if (r < low || l > high) {
		return -1;
	}
	if (low >= l && high <= r) {
		return seg[ind];
	}
	int mid = (low + high) >> 1;
	int left = query(2 * ind + 1, low, mid, l, r);
	int right = query(2 * ind + 2, mid + 1, high, l, r);
	if (left == -1) return right;
	if (right == -1) return left;
	return (height[left] < height[right]) ? left : right;
}

signed main() {
	int t = 1;
	int tc = 1;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 0; i <= N; i++) {
			adj[i].clear();
		}
		euler.clear();
		height.clear();
		firstOcc.clear();

		for (int i = 0; i < n; i++) {
			int m;
			cin >> m;
			for (int j = 0; j < m; j++) {
				int x;
				cin >> x;
				--x;
				adj[i].pb(x);
				adj[x].pb(i);
			}
		}

		dfs(0);
		int m = euler.size();
		seg = vector<int>(4 * m);
		build(0, 0, m - 1);

		int q;
		cin >> q;
		while (q--) {
			int u, v;
			cin >> u >> v;
			--u, --v;
			int l = firstOcc[u];
			int r = firstOcc[v];
			if (l > r) swap(l, r);
			cout << query(0, 0, m - 1, l, r) + 1 << el;
		}
	}
	return 0;
}
