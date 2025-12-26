#include <stdio.h>
#include <vector>

// https://leetcode.cn/problems/validate-binary-search-tree/

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
    //1. 二叉树中序遍历
    //中序遍历天然升序，遍历过程中往数组中添加节点值，如果比前一个值小则表示不是合法的二叉树
    bool isValidBST(TreeNode* root) 
    {
        if (root == nullptr)
        {
            return false;
        }

        vector<int> values;
        return this->recursive(root, values);
    }

    bool recursive(TreeNode* node, vector<int>& values)
    {
        if (node->left != nullptr && !this->recursive(node->left, values))
        {
            return false;
        }
        if (values.size() > 0 && values[values.size()-1] >= node->val)
        {
            return false;
        }
        values.push_back(node->val);
        if (node->right != nullptr && !this->recursive(node->right, values))
        {
            return false;
        }
        return true;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: root = [2,1,3]
//     //输出: true
//     TreeNode* n1_1 = new TreeNode(2);
//     TreeNode* n1_2 = new TreeNode(1);
//     TreeNode* n1_3 = new TreeNode(3);
//     n1_1->left = n1_2;
//     n1_1->right = n1_3;
//     bool result = s.isValidBST(n1_1);

//     //输入: root = [5,1,4,null,null,3,6]
//     //输出: false
//     TreeNode* n2_1 = new TreeNode(5);
//     TreeNode* n2_2 = new TreeNode(1);
//     TreeNode* n2_3 = new TreeNode(4);
//     TreeNode* n2_4 = new TreeNode(3);
//     TreeNode* n2_5 = new TreeNode(6);
//     n2_1->left = n2_2;
//     n2_1->right = n2_3;
//     n2_3->left = n2_4;
//     n2_3->right = n2_5;
//     result = s.isValidBST(n2_1);

//     //[5,4,6,null,null,3,7]
//     TreeNode* n3_1 = new TreeNode(5);
//     TreeNode* n3_2 = new TreeNode(4);
//     TreeNode* n3_3 = new TreeNode(6);
//     TreeNode* n3_4 = new TreeNode(3);
//     TreeNode* n3_5 = new TreeNode(7);
//     n3_1->left = n3_2;
//     n3_1->right = n3_3;
//     n3_3->left = n3_4;
//     n3_3->right = n3_5;
//     result = s.isValidBST(n3_1);

//     return 0;
// }