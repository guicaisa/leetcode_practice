#include <vector>

// https://leetcode.cn/problems/binary-tree-level-order-traversal/

using namespace std;

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution 
{
public:
    //1. 广度优先搜索
    //逐层遍历每一层的所有节点，并记录结果即可
    vector<vector<int>> levelOrder(TreeNode* root) 
    {
        if (root == nullptr)
        {
            return vector<vector<int>>();
        }
        
        vector<vector<int>> results;
        vector<TreeNode*> layer_nodes = {root};
        vector<TreeNode*> next_layer_nodes;
        while (layer_nodes.size() > 0)
        {
            vector<int> temp_results;
            for (int i = 0; i < layer_nodes.size(); ++i)
            {
                TreeNode* node = layer_nodes[i];
                if (node->left != nullptr)
                {
                    next_layer_nodes.push_back(node->left);
                }
                if (node->right != nullptr)
                {
                    next_layer_nodes.push_back(node->right);
                }
                temp_results.push_back(node->val);
            }

            results.push_back(temp_results);
            layer_nodes = next_layer_nodes;
            next_layer_nodes.clear();
        }

        return results;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: root = [3,9,20,null,null,15,7]
//     //输出: [[3],[9,20],[15,7]]
//     TreeNode* n1_1 = new TreeNode(3);
//     TreeNode* n1_2 = new TreeNode(9);
//     TreeNode* n1_3 = new TreeNode(20);
//     TreeNode* n1_4 = new TreeNode(15);
//     TreeNode* n1_5 = new TreeNode(7);
//     n1_1->left = n1_2;
//     n1_1->right = n1_3;
//     n1_3->left = n1_4;
//     n1_3->right = n1_5;
//     vector<vector<int>> results = s.levelOrder(n1_1);

//     //输入: root = [1]
//     //输出: [[1]]
//     TreeNode* n2_1 = new TreeNode(1);
//     results = s.levelOrder(n2_1);

//     //输入: root = []
//     //输出: []
//     results = s.levelOrder(nullptr);

//     return 0;
// }