#include <stdio.h>

// https://leetcode.cn/problems/path-sum/

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
    bool hasPathSum(TreeNode* root, int targetSum) 
    {
        if (root == nullptr)
        {
            return false;
        }
        return this->recursive(root, targetSum, 0);
    }

    bool recursive(TreeNode* node, int targetSum, int curSum)
    {
        curSum += node->val;
        if (node->left == nullptr && node->right == nullptr && curSum == targetSum)
        {
            return true;
        }
        if (node->left != nullptr && this->recursive(node->left, targetSum, curSum))
        {            
            return true;
        }
        if (node->right != nullptr && this->recursive(node->right, targetSum, curSum))
        {
            return true;
        }
        return false;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
//     //输出: true
//     TreeNode* node1_1 = new TreeNode(5);
//     TreeNode* node1_2 = new TreeNode(4);
//     TreeNode* node1_3 = new TreeNode(8);
//     TreeNode* node1_4 = new TreeNode(11);
//     TreeNode* node1_5 = new TreeNode(13);
//     TreeNode* node1_6 = new TreeNode(4);
//     TreeNode* node1_7 = new TreeNode(7);
//     TreeNode* node1_8 = new TreeNode(2);
//     TreeNode* node1_9 = new TreeNode(1);
//     node1_1->left = node1_2;
//     node1_1->right = node1_3;
//     node1_2->left = node1_4;
//     node1_4->left = node1_7;
//     node1_4->right = node1_8;
//     node1_3->left = node1_5;
//     node1_3->right = node1_6;
//     node1_6->right = node1_9;
//     bool result = s.hasPathSum(node1_1, 22);

//     //输入: root = [1,2,3], targetSum = 5
//     //输出: false
//     TreeNode* node2_1 = new TreeNode(1);
//     TreeNode* node2_2 = new TreeNode(2);
//     TreeNode* node2_3 = new TreeNode(3);
//     node2_1->left = node2_2;
//     node2_1->right = node2_3;
//     result = s.hasPathSum(node2_1, 5);

//     //输入: root = [], targetSum = 0
//     //输出: false
//     result = s.hasPathSum(nullptr, 0);

//     return 0;
// }