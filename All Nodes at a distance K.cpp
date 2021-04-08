/*
 Author: elite__coder
 LeetCode: https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    unordered_map<TreeNode*, TreeNode*> parent;
    unordered_map<TreeNode*, int> visited;
public:
    void dfs(TreeNode* node, TreeNode* par=nullptr){
        if(node == nullptr)
            return;
        parent[node] = par;
        dfs(node->left, node);
        dfs(node->right, node);
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        if(root == nullptr)
            return {};
        vector<int> vec;
        dfs(root);
        
        queue<pair<TreeNode*, int>> q;
        q.push({target, 0});
        while(!q.empty()){
            auto it = q.front().first;
            visited[it]++;
            int level = q.front().second;
            q.pop();
            if(level == K)
                vec.push_back(it->val);
            if(it->left!=nullptr && visited.find(it->left)==visited.end())
                q.push({it->left, level+1});
            if(it->right!=nullptr && visited.find(it->right)==visited.end())
                q.push({it->right, level+1});
            if(parent[it]!=nullptr && visited.find(parent[it])==visited.end())
                q.push({parent[it], level+1});
        }
        return vec;
    }
};
