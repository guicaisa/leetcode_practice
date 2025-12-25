#include <vector>

// https://leetcode.cn/problems/binary-tree-right-side-view/

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
    //从根节点开始，维护一个当前层所有节点的数组
    //在遍历当前层所有节点的同时，获取下层的所有节点并存储在临时数组中
    //遍历结束时，将当前层最后一个节点的值存入结果数组中，然后下次遍历时处理下一层的所有节点，直到最后一层节点全部处理完
    vector<int> rightSideView(TreeNode* root) 
    {
        if (root == nullptr)
        {
            return vector<int>();
        }
        vector<int> results;
        vector<TreeNode*> layer_nodes = {root};
        vector<TreeNode*> next_layer_nodes;
        while (layer_nodes.size() > 0)
        {
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
                if (i == layer_nodes.size() - 1)
                {
                    results.push_back(node->val);
                }
            }
            layer_nodes = next_layer_nodes;
            next_layer_nodes.clear();
        }

        return results;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: root = [1,2,3,null,5,null,4]
//     //输出: [1,3,4]
//     TreeNode* n1_1 = new TreeNode(1);
//     TreeNode* n1_2 = new TreeNode(2);
//     TreeNode* n1_3 = new TreeNode(3);
//     TreeNode* n1_4 = new TreeNode(5);
//     TreeNode* n1_5 = new TreeNode(4);
//     n1_1->left = n1_2;
//     n1_1->right = n1_3;
//     n1_2->right = n1_4;
//     n1_3->right = n1_5;
//     vector<int> result = s.rightSideView(n1_1);

//     //输入: root = [1,2,3,4,null,null,null,5]
//     //输出: [1,3,4,5]
//     TreeNode* n2_1 = new TreeNode(1);
//     TreeNode* n2_2 = new TreeNode(2);
//     TreeNode* n2_3 = new TreeNode(3);
//     TreeNode* n2_4 = new TreeNode(4);
//     TreeNode* n2_5 = new TreeNode(5);
//     n2_1->left = n2_2;
//     n2_1->right = n2_3;
//     n2_2->left = n2_4;
//     n2_4->left = n2_5;
//     result = s.rightSideView(n2_1);

//     //输入: root = [1,null,3]
//     //输出: [1,3]
//     TreeNode* n3_1 = new TreeNode(1);
//     TreeNode* n3_2 = new TreeNode(3);
//     n3_1->right = n3_2;
//     result = s.rightSideView(n3_1);

//     //输入：root = []
//     //输出：[]
//     result = s.rightSideView(nullptr);

//     return 0;
// }