#include <stdio.h>

// https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/

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
    //1. 深度优先搜索
    //探索到左子树最深的节点，然后往上层返回作为下一个节点，连接右子树节点
    void flatten(TreeNode* root) 
    {
        if (root == nullptr)
        {
            return;
        }
        this->recursive(root);
    }
    
    TreeNode* recursive(TreeNode* node)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            return node;
        }
        TreeNode* pre = node;
        TreeNode* next = nullptr;
        TreeNode* left = node->left;
        TreeNode* right = node->right;
        if (left != nullptr)
        {
            pre = this->recursive(left);
        }
        if (right != nullptr)
        {
            next = this->recursive(right);
        }
        node->left = nullptr;
        node->right = left != nullptr ? left : right;
        pre->right = right;
        return next != nullptr ? next : pre;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     //输入: root = [1,2,5,3,4,null,6]
//     //输出: [1,null,2,null,3,null,4,null,5,null,6]
//     TreeNode* n1_1 = new TreeNode(1);
//     TreeNode* n1_2 = new TreeNode(2);
//     TreeNode* n1_3 = new TreeNode(5);
//     TreeNode* n1_4 = new TreeNode(3);
//     TreeNode* n1_5 = new TreeNode(4);
//     TreeNode* n1_6 = new TreeNode(6);
//     n1_1->left = n1_2;
//     n1_1->right = n1_3;
//     n1_2->left = n1_4;
//     n1_2->right = n1_5;
//     n1_3->right = n1_6;
//     s.flatten(n1_1);

//     //输入: root = []
//     //输出: []
//     TreeNode* n2_1 = nullptr;
//     s.flatten(n2_1);

//     //输入: root = [0]
//     //输出: [0]
//     TreeNode* n3_1 = new TreeNode(0);
//     s.flatten(n3_1);

//     return 0;
// }