/*
 Author: @elite__coder
 Problem Link: https://leetcode.com/problems/kth-ancestor-of-a-tree-node/
*/

class TreeAncestor {
public:
    vector<int> depth;
    vector<vector<int>> up;
    TreeAncestor(int n, vector<int>& parent) {
        int LOG = log2(n)+1;
        depth = vector<int>(n);
        up = vector<vector<int>>(n, vector<int>(LOG));
        parent[0] = 0;
        for(int v=0;v<n;v++){
            if(v!=0)
                depth[v] = depth[parent[v]]+1;
            up[v][0] = parent[v];
        }
        for(int i=1;i<LOG;i++){
            for(int v=0;v<n;v++){
                up[v][i] = up[up[v][i-1]][i-1];
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        if(depth[node]<k)
            return -1;
        for(int i=0;(1<<i)<=k;i++){
            if(k&(1<<i))
                node = up[node][i];
        }
        return node;
    }
};
