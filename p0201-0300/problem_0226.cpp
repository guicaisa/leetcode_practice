#include <stdio.h>

// https://leetcode.cn/problems/invert-binary-tree/

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
    //1. 递归
    //如果树的左右子树不为空，则翻转左右子树，用递归的形式一直往下层进行调用
    //并在调用结束之后，将左右子树进行交换，即可得到结果
    TreeNode* invertTree(TreeNode* root) 
    {
        if (root == nullptr)
        {
            return root;
        }
        if (root->left == nullptr && root->right == nullptr)
        {
            return root;
        }
        if (root->left != nullptr)
        {
            this->invertTree(root->left);
        }
        if (root->right != nullptr)
        {
            this->invertTree(root->right);
        }
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
        return root;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     TreeNode* n1_1 = new TreeNode(4);
//     TreeNode* n1_2 = new TreeNode(2);
//     TreeNode* n1_3 = new TreeNode(7);
//     TreeNode* n1_4 = new TreeNode(1);
//     TreeNode* n1_5 = new TreeNode(3);
//     TreeNode* n1_6 = new TreeNode(6);
//     TreeNode* n1_7 = new TreeNode(9);
//     n1_1->left = n1_2;
//     n1_1->right = n1_3;
//     n1_2->left = n1_4;
//     n1_2->right = n1_5;
//     n1_3->left = n1_6;
//     n1_3->right = n1_7;
//     TreeNode* result = s.invertTree(n1_1);

//     TreeNode* n2_1 = new TreeNode(2);
//     TreeNode* n2_2 = new TreeNode(1);
//     TreeNode* n2_3 = new TreeNode(3);
//     n2_1->left = n2_2;
//     n2_1->right = n2_3;
//     result = s.invertTree(n2_1);

//     return 0;
// }